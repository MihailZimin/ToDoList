#ifndef MAINWINDOW
#define MAINWINDOW


#include <iostream>
#include <Graph_lib/Graph.h>
#include <Graph_lib/GUI.h>
#include <Graph_lib/Window.h>
#include <vector>
#include "DayWork/MyWidgets.h"
#include "DayWork/TaskWindow.h"
#include "DayWork/ChangeTaskInfo.h"
#include "DayWork/TaskWindow.h"
#include "DayWork/PARAMETERS.h"
#include "date_button.h"

using namespace Graph_lib;

class WeekWindow : public Graph_lib::Window
{
    public:
        WeekWindow(Point xy, int h, int w);
        ~WeekWindow();
        void years_page();
        void add_years();
        void week_page();
        void back_page();

    private:
        int current_year{Chrono_ns::today().year()};
        std::vector<std::vector<DateButton*>> years{1};
        DateButton Monday;
        DateButton Tuesday;
        DateButton Wednesday;
        DateButton Thursday;
        DateButton Friday;
        DateButton Saturday;
        DateButton Sunday;
        Text current_date;
        Button next;
        Button prev;
        Button add_years_btn;
        Button week_page_btn;
        int year_page_counter;
        static void cb_day(Address, Address);
        static void cb_years(Address, Address);
        static void current_year_cb(Address, Address);
        static void cb_add_years(Address, Address);
        static void cb_week_page(Address, Address);
        static void cb_back(Address, Address);

        void show_day(DateButton& btn);
        void show_current_year(DateButton& btn);
};

#endif //MAINWINDOW