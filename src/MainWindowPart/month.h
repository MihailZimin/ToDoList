#ifndef MONTH
#define MONTH

#include "MainWindow.h"

class Month: public Graph_lib::Window
{
    public:
        Month(DateButton* month, WeekWindow* week_win, const std::string month_name, const std::string year_number);
        ~Month();
        void hide_window();
    private:
        WeekWindow* week_win;
        DateButton* month_button;
        Button week_page_btn;
        const std::string month_name; 
        std::vector<DateButton*> days;
        static void current_day_cb(Address, Address);
        static void main_page_cb(Address, Address);
};

#endif //MONTH
