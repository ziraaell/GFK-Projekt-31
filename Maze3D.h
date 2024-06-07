#pragma once
#include <wx/wx.h>
#include "Player.h"

enum class FIELD { PLAYER, WALL, FLOOR, EXIT };

class Maze3D : public wxFrame 
{
public:
    Maze3D(const std::string& title, const std::string& filename);
    void LoadMapFromFile(const std::string& filename);
    //void FindStart();
    void OnPaint(wxPaintEvent& event);
    void Render3D(wxDC& dc);
    void RenderMap(wxDC& dc);
    void OnKeyDown(wxKeyEvent& event);
    void OnKeyUp(wxKeyEvent& event);
    void HandleMovement();
    void DisplayTime();
    ~Maze3D();

private:
    bool keys[4] = {false, false, false, false};
    bool shiftPressed = false;
    //std::vector<std::string> maze;
    std::vector <std::vector <FIELD>> Fields;
    int width, height;
    Player player;
    time_t startTime;
    bool gameEnded = false;
};
