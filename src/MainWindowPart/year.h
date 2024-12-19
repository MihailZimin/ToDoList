#ifndef YEAR
#define YEAR

#include "MainWindow.h"

using namespace Graph_lib;

class Year: public Graph_lib::Window
{
<<<<<<< HEAD
public:
    Year(Graph_lib::Point pos, DateButton* btn, WeekWindow* week_win, std::string year_number);
    ~Year();
    void current_month(DateButton& btn);
    void hide_window();
private:
    WeekWindow* week_win;
    DateButton* year_button;
    Button week_page_btn;
    std::string year_number;
    Text current_year_text;
    std::vector<DateButton*> months;
    static void current_month_cb(Address, Address);
    static void main_page_cb(Address, Address);
=======
    public:
        Year(Graph_lib::Point pos, DateButton* btn, WeekWindow* week_win, std::string year_number);
        ~Year();
        void current_month(DateButton& btn);
        void hide_window();
    private:
        WeekWindow* week_win;
        DateButton* year_button;
        Button week_page_btn;
        std::string year_number;
        Text current_year_text;
        std::vector<DateButton*> months;
        static void current_month_cb(Address, Address);
        static void main_page_cb(Address, Address);
>>>>>>> origin/main
};

#endif //YEAR