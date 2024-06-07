#include "Maze3D.h"
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>
//#include <wx/dcmemory.h>
//#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <iostream>

const int SCREEN_WIDTH = 800, SCREEN_HEIGHT = 600;
const int TILE_SIZE = 5;
const int MAP_SCALE = 1;
const float FOV = M_PI / 3;
const float DEPTH = 50.0;
const float SPEED = 0.3, TURNSPEED = 0.05;

Maze3D::Maze3D(const std::string& title, const std::string& file) : wxFrame(NULL, wxID_ANY, title)
{
	SetSize(0, 0, 800, 600);
	Center();

	LoadMapFromFile(file);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

	Bind(wxEVT_PAINT, &Maze3D::OnPaint, this);
	Bind(wxEVT_KEY_DOWN, &Maze3D::OnKeyDown, this);
	Bind(wxEVT_KEY_UP, &Maze3D::OnKeyUp, this);
	startTime = time(nullptr);
}


void Maze3D::LoadMapFromFile(const std::string& filename) {
    std::string line;
    std::vector<std::string> out;

    std::ifstream in(filename.c_str());

    if (!in) 
    {
        wxMessageBox(_("Unable to load file " + filename));
        exit(1);
    }

    std::getline(in, line);
    if (sscanf(line.c_str(), "%d,%d", &width, &height) != 2) 
    {
        wxMessageBox(_("Invalid maze size"));
        exit(1);
    }

    while (std::getline(in, line))
        out.push_back(line);
    in.close();

    Fields.resize(height, std::vector<FIELD>(width));

    for (int y = 0; y < height; y++) 
    {
        for (int x = 0; x < width; x++) 
        {
            switch (out[y][x])
            {
            case 'X': Fields[y][x] = FIELD::WALL; break;
            case ' ': Fields[y][x] = FIELD::FLOOR; break;
            case 's': Fields[y][x] = FIELD::PLAYER;
                player.pos_x = x * TILE_SIZE + TILE_SIZE / 2;
                player.pos_y = y * TILE_SIZE + TILE_SIZE / 2;
                player.angle = 0.0;
                player.speed = SPEED;
                player.turnSpeed = TURNSPEED; break;
            case 'E': Fields[y][x] = FIELD::EXIT; break;
            }
        }
    }
}

void Maze3D::OnPaint(wxPaintEvent& event) 
{
	wxAutoBufferedPaintDC dc(this);
	Render3D(dc);
}

void Maze3D::Render3D(wxDC& dc) 
{
	dc.SetBrush(wxBrush(wxColour(135, 206, 235)));
	dc.DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

	dc.SetBrush(wxBrush(wxColour(0, 128, 0)));
	dc.DrawRectangle(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);

	float rayAngle = player.angle - FOV / 2;
	for (int ray = 0; ray < SCREEN_WIDTH; ++ray) {
		for (float dist = 0; dist < DEPTH; dist += 0.02) 
		{	
			float rayX = player.pos_x + dist * cos(rayAngle);
			float rayY = player.pos_y + dist * sin(rayAngle);

			int mapX = (int)(rayX / TILE_SIZE);
			int mapY = (int)(rayY / TILE_SIZE);

			if (mapX < 0 || mapX >= width || mapY < 0 || mapY >= width || Fields[mapY][mapX] == FIELD::WALL) 
            {
				float wallHeight = SCREEN_HEIGHT / (dist * cos(rayAngle - player.angle)) * 1.5;

                int shade = 255 - (int)(dist * 9.5);
                if (shade < 0) shade = 0;

                dc.SetPen(wxPen(wxColour(shade/255.0 * 139, shade/255.0 * 69, shade/255.0 * 19), 1));
				dc.DrawLine(ray, (SCREEN_HEIGHT / 2.0) - wallHeight / 2, ray, (SCREEN_HEIGHT / 2.0) + wallHeight / 2.0);
				break;
			}
		}
		rayAngle += FOV / SCREEN_WIDTH;
	}

	//RenderMap(dc);
}

//void Maze3D::RenderMap(wxDC& dc) 
//{
//    for (int y = 0; y < height; ++y) {
//        for (int x = 0; x < width; ++x) 
//        {
//            if (Fields[y][x] == FIELD::WALL) 
//                dc.SetBrush(wxBrush(wxColour(139, 69, 19)));
//            else if (Fields[y][x] == FIELD::EXIT)
//                dc.SetBrush(wxBrush(wxColour(0, 255, 0)));
//            else
//                continue;
//
//            dc.DrawRectangle(x * TILE_SIZE / MAP_SCALE, y * TILE_SIZE / MAP_SCALE, TILE_SIZE / MAP_SCALE, TILE_SIZE / MAP_SCALE);
//        }
//    }
//    dc.SetBrush(wxBrush(wxColour(255, 0, 0)));
//    dc.DrawRectangle(player.GetX() / MAP_SCALE - 2, player.GetY() / MAP_SCALE - 2, 4, 4);
//}

void Maze3D::OnKeyDown(wxKeyEvent& event) 
{
    switch (event.GetKeyCode()) 
    {
    case WXK_UP: keys[0] = true; break;
    case WXK_DOWN: keys[1] = true; break;
    case WXK_LEFT: keys[2] = true; break;
    case WXK_RIGHT: keys[3] = true; break;
    case WXK_SHIFT: shiftPressed = true; break;
    }
    HandleMovement();
    Refresh();
}

void Maze3D::OnKeyUp(wxKeyEvent& event) 
{
    switch (event.GetKeyCode()) {
    case WXK_UP: keys[0] = false; break;
    case WXK_DOWN: keys[1] = false; break;
    case WXK_LEFT: keys[2] = false; break;
    case WXK_RIGHT: keys[3] = false; break;
    case WXK_SHIFT: shiftPressed = false; break;
    }
    HandleMovement();
    Refresh();
}

void Maze3D::HandleMovement() 
{
    float moveStep = player.speed * (shiftPressed ? 2 : 1);
    float newX = player.pos_x, newY = player.pos_y;


    if (keys[0]) // UP
    { 
        newX += moveStep * cos(player.angle);
        newY += moveStep * sin(player.angle);
    }
    if (keys[1]) // DOWN
    { 
        newX -= moveStep * cos(player.angle);
        newY -= moveStep * sin(player.angle);
    }
    if (keys[2]) // LEFT
    { 
        player.angle = player.angle - player.turnSpeed;
        if (player.angle < 0) player.angle = player.angle + 2 * M_PI;
    }
    if (keys[3]) // RIGHT
    { 
        player.angle= player.angle + player.turnSpeed;
        if (player.angle > 2 * M_PI)  player.angle = player.angle - 2 * M_PI;
    }

    int mapX = (int)(newX / TILE_SIZE);
    int mapY = (int)(newY / TILE_SIZE);

    if (mapX >= 0 && mapX < width && mapY >= 0 && mapY < height && Fields[mapY][mapX] != FIELD::WALL)
    {
        player.pos_x = newX;
        player.pos_y = newY;
    }

    if (Fields[mapY][mapX] == FIELD::EXIT) 
    {
        gameEnded = true;
        DisplayTime();
    }
}

void Maze3D::DisplayTime() 
{
    time_t koniecCzasu = time(nullptr);
    double czas = difftime(koniecCzasu, startTime);
    wxMessageBox("Ukoñczono labirynt w czasie: " + std::to_string(czas) + " sekund.", "Koniec gry", wxICON_INFORMATION);
}

Maze3D::~Maze3D() {}