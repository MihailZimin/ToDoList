#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
#include "Graph_lib/GUI.h"
#include "MyWidgets.h"


void MyButton::attach(Graph_lib::Window& win)
{
    pw = new Fl_Button{loc.x, loc.y, width, height, label.c_str()};
    pw->callback(reinterpret_cast<Fl_Callback*>(do_it), this);  // pass this widget
    pw->color(color);
    own = &win;
}


void MyButton::move_to_coordinates(int x, int y) {
    hide();
    loc.x = x;
    loc.y = y;
    pw->position(loc.x, loc.y);
    show();
}


void MyIn_box::attach(Graph_lib::Window& win)
{
    pw = new Fl_Input{loc.x, loc.y, width, height, label.c_str()};
    pw->color(col);
    Fl_Input& pi = Graph_lib::reference_to<Fl_Input>(pw);
    pi.insert(inside_text.c_str());
    own = &win;
}
