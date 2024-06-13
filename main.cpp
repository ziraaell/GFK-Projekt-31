/**
 * @file MyApp.cpp
 * @brief Plik zawiera klasę MyApp, która jest punktem wejścia aplikacji wxWidgets.
 */

#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>
#include "Maze3D.h"


/**
 * @class MyApp
 * @brief Klasa aplikacji, dziedzicząca po wxApp, odpowiedzialna za inicjalizację i uruchomienie głównego okna aplikacji.
 * 
 * MyApp odpowiada za utworzenie i wyświetlenie głównego okna aplikacji oraz załadowanie potrzebnych zasobów.
 */
class MyApp : public wxApp {
public:
/**
     * @brief Inicjalizuje aplikację.
     * 
     * Tworzy i wyświetla główne okno aplikacji. Ładuje główny widok z pliku labirynt.txt.
     * @return true jeśli inicjalizacja przebiegła pomyślnie, false w przeciwnym razie.
     */
    virtual bool OnInit() 
    {
        Maze3D* maze = new Maze3D("Labirynt 3D", "labirynt.txt");
        maze->Show(true);
        return true;
    }
};

/**
 * @brief Makro odpowiedzialne za implementację głównego punktu wejścia aplikacji wxWidgets.
 * 
 * wxIMPLEMENT_APP(MyApp) implementuje główną pętlę programu oraz inicjalizuje aplikację wxWidgets.
 */
wxIMPLEMENT_APP(MyApp);
