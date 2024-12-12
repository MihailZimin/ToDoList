#ifndef YEAR
#define YEAR

#include "month.h"

using namespace Graph_lib;

class Year: public Graph_lib::Window
{
    public:
        Year(DateButton* btn, WeekWindow* week_win, const std::string year_number);
        ~Year();
        void current_month(DateButton& btn);
        void hide_window();
    private:
        WeekWindow* week_win;
        DateButton* year_button;
        Button week_page_btn;
        const std::string year_number;
        std::vector<DateButton*> months;
        static void current_month_cb(Address, Address);
        static void main_page_cb(Address, Address);
};

#endif //YEAR