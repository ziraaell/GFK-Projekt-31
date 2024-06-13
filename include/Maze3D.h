#pragma once
#include <wx/wx.h>
#include "Player.h"

/**
 * @enum FIELD
 * @brief Typ wyliczeniowy reprezentujący rodzaje pól w labiryncie.
 */
enum class FIELD { PLAYER, WALL, FLOOR, EXIT };

/**
 * @class Maze3D
 * @brief Klasa głównego okna aplikacji, obsługująca logikę i wyświetlanie 3D labiryntu.
 *
 * Maze3D dziedziczy po wxFrame i zarządza wszystkimi głównymi aspektami interakcji z użytkownikiem oraz
 * wizualizacją i obsługą logiki gry labirynt.
 */
class Maze3D : public wxFrame 
{
public:
    Maze3D(const std::string& title, const std::string& filename);
    void LoadMapFromFile(const std::string& filename);
    void OnPaint(wxPaintEvent& event);
    void Render3D(wxDC& dc);
    void RenderMap(wxDC& dc);
    void OnKeyDown(wxKeyEvent& event);
    void OnKeyUp(wxKeyEvent& event);
    void HandleMovement();
    void DisplayTime();
    ~Maze3D();

private:
    bool keys[4] = {false, false, false, false}; ///< Statusy klawiszy: UP, DOWN, LEFT, RIGHT
    bool shiftPressed = false;                  ///< Status klawisza SHIFT
    std::vector <std::vector <FIELD>> Fields;   ///< Struktura przechowująca typy pól labiryntu
    int width, height;                          ///< Wymiary labiryntu
    Player player;                              ///< Obiekt gracza
    time_t startTime;                           ///< Czas rozpoczęcia gry
    bool gameEnded = false;                     ///< Flaga końca gry
    bool FPP = true;                            ///< Flaga widoku pierwszoosobowego (First Person Perspective)

    enum {
        ID_1 = 1001, ///< ID dla menu zmiany na widok pierwszoosobowy
        ID_2 = 1002, ///< ID dla menu zmiany na widok z góry
    };
};
