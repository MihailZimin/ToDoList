#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
#include "Graph_lib/GUI.h"
#include "MyButton.h"


void MyButton::attach(Graph_lib::Window& win)
{
    pw = new Fl_Button{loc.x, loc.y, width, height, label.c_str()};
    pw->callback(reinterpret_cast<Fl_Callback*>(do_it), this);  // pass this widget
    pw->color(color);
    own = &win;
}