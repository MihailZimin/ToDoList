#include "date_button.h"
#include <map>
#include <ctime>
#include <string>

std::string DateButton::get_day_of_week(int day, const std::string& month, int year) {
    std::map<std::string, int> month_map = {
        {"January", 1}, {"February", 2}, {"March", 3},
        {"April", 4}, {"May", 5}, {"June", 6},
        {"July", 7}, {"August", 8}, {"September", 9},
        {"October", 10}, {"November", 11}, {"December", 12}
    };

    int m = month_map[month];

    std::tm time_in = {0}; 

    time_in.tm_year = year - 1900; 
    time_in.tm_mon = m - 1;        
    time_in.tm_mday = day;

    std::time_t time_temp = std::mktime(&time_in);

    int day_of_week = std::localtime(&time_temp)->tm_wday;

    std::vector<std::string> days = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    return days[day_of_week];
}


void DateButton::attach(Graph_lib::Window& win) {
    pw = new Fl_Button{loc.x, loc.y, width, height, label.c_str()};
    pw->callback(reinterpret_cast<Fl_Callback*>(do_it), this);  // pass this widget
    pw->color(color);
    own = &win;
}

void DateButton::set_color() {
    pw->color(color);
}



void colorButton(DateButton* btn, int count_of_tasks) {
    if (count_of_tasks <= 5) {
        btn->color = FL_GREEN;
    }
    else if (count_of_tasks <= 10) {
        btn->color = FL_YELLOW;
    }
    else {
        btn->color = FL_RED;
    }
}
