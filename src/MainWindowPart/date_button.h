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
    std::string get_label() { return label; };
    std::string get_day_of_week(int day, const std::string& month, int year);
    Chrono_ns::Date date;
};





#endif //DATE_BUTTON