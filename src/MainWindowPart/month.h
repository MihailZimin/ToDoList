#ifndef MONTH
#define MONTH

#include "year.h"

class Month: public Graph_lib::Window
{
    public:
        Month(DateButton* month, Year* year_win, std::string month_name, std::string year_number);
        ~Month();
        void hide_window();
        std::string month_name;
    private:
        Year* year_win;
        DateButton* month_button;
        Button back_page_btn;
        std::string year_number;
        std::vector<DateButton*> days;
        Text current_month_text;
        static void current_day_cb(Address, Address);
        static void back_page_cb(Address, Address);

        void current_day(DateButton& btn);
};

#endif //MONTH
