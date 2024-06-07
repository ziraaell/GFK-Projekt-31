#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>
#include "include/Maze3D.h"

class MyApp : public wxApp {
public:
    virtual bool OnInit() 
    {
        Maze3D* maze = new Maze3D("Labirynt 3D", "labirynt.txt");
        maze->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);