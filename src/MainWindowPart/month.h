#ifndef MONTH
#define MONTH

#include "MainWindow.h"

class Month: public Graph_lib::Window
{
    public:
        Month(Button* month, WeekWindow* week_win, const std::string month_name);
        WeekWindow* week_win;
        Button* month_button;
    private:
        static void current_day_cb(Address, Address);
        static void main_page_cb(Address, Address);
        void hide_window();
        Button main_page_btn;
        const std::string month_name; 
        std::vector<Button*> days;
};

#endif //MONTH
