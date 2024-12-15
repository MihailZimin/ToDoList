#ifndef DATE_BUTTON
#define DATE_BUTTON

#include <Graph_lib/GUI.h>
#include "toDoListFileWork/to_do_list/chrono.h"

using namespace Graph_lib;


struct DateButton: public Button
{
    DateButton(Point xy, int w, int h, const std::string& label, Callback cb, Chrono_ns::Date date) : 
    Button{xy, w, h, label, cb}, 
    date{date} 
    {}
    DateButton(Point xy, int w, int h, const std::string& label, Callback cb) : 
    Button{xy, w, h, label, cb}, 
    date{date} 
    {}
    DateButton(Graph_lib::Point xy, int w, int h, const std::string& label,
        Graph_lib::Callback cb, Fl_Color color) : color(color), Button{xy, w, h, label, cb}{}


    std::string get_label() { return label; };
    std::string get_day_of_week(int day, const std::string& month, int year);

    void attach(Graph_lib::Window &) override;
    void set_color();

    Chrono_ns::Date date;
    Fl_Color color{fl_rgb_color(192, 192, 192)};
};


void colorButton(DateButton* btn, int count_of_tasks);


#endif //DATE_BUTTON