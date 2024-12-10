#ifndef YEAR
#define YEAR

#include "month.h"

using namespace Graph_lib;

class Year: public Graph_lib::Window
{
    public:
        Year(Button* btn, WeekWindow* week_win, const std::string year_number);
        WeekWindow* week_win;
    private:
        const std::string year_number;
        std::vector<Button*> months;
        Button* year_button;
        Button main_page_btn;
        void current_year(Button& btn);
        void hide_window();
        static void current_month_cb(Address, Address);
        static void main_page_cb(Address, Address);
};

#endif //YEAR