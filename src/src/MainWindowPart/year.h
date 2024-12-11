#ifndef YEAR
#define YEAR

#include "month.h"

using namespace Graph_lib;

class Year: public Graph_lib::Window
{
    public:
        Year(DateButton* btn, WeekWindow* week_win, const std::string year_number);
        WeekWindow* week_win;
    private:
        const std::string year_number;
        std::vector<DateButton*> months;
        DateButton* year_button;
        Button main_page_btn;
        void current_year(DateButton& btn);
        void hide_window();
        static void current_month_cb(Address, Address);
        static void main_page_cb(Address, Address);
};

#endif //YEAR