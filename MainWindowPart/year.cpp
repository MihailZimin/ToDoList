#include "year.h"

std::vector<std::string> Months_names
{
    "September",
    "October",
    "November",
    "December",
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August"
};

Year::Year(Button* btn, WeekWindow* win, const std::string year_number): 
    Window{Point(100,100), 600, 400, year_number},
    year_button{btn},
    week_win {win},
    main_page_btn{Point(x_max() - 100,y_max() - 80), 100, 80, "Week page", main_page_cb} 
{
    for (int j = 0; j < 3; ++j)
    {
        Button* month_button = new Button{Point{20, 20 + 80*j}, 100, 80, Months_names[j], current_month_cb};
        months.push_back(month_button);
    }
    for (int j = 3; j < 6; ++j)
    {
        Button* month_button = new Button{Point{130, 20 + 80*(j-3)}, 100, 80, Months_names[j], current_month_cb};
        months.push_back(month_button);
    }
    for (int j = 6; j < 9; ++j)
    {
        Button* month_button = new Button{Point{240, 20 + 80*(j-6)}, 100, 80, Months_names[j], current_month_cb};
        months.push_back(month_button);
    }
        for (int j = 9; j < 12; ++j)
    {
        Button* month_button = new Button{Point{350, 20 + 80*(j-9)}, 100, 80, Months_names[j], current_month_cb};
        months.push_back(month_button);
    }
    for (size_t i = 0; i < months.size(); ++i)
    {
        attach(*months[i]);
    }
    attach(main_page_btn);
}

void Year::hide_window()
{
    week_win->show();
    hide();
}

void Year::current_month_cb(Address, Address pw)
{
    auto& btn = Graph_lib::reference_to<Button>(pw);
    Month* month_window = new Month(&btn, &reinterpret_cast<WeekWindow&>(btn.window()), btn.get_label());
    dynamic_cast<Year&&>(btn.window()).hide();
}

void Year::main_page_cb(Address, Address pw)
{
    auto& btn = Graph_lib::reference_to<Button>(pw);
    reinterpret_cast<Year&>(btn.window()).hide_window();
}