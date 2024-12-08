#include "year.h"

Month::Month(Button* month_button, WeekWindow* week_win): 
    Window{Point(100,100), 600, 400, "Month"},
    month_button{month_button}, 
    week_win{week_win},
    main_page_btn{Point(x_max() - 100,y_max() - 80), 100, 80, "Week page", main_page_cb} 
{
    for (int j = 1; j < 6; ++j)
    {
        Button* day_button = new Button{Point{20, 20 + 40*j}, 60, 40, std::to_string(j), current_day_cb};
        days.push_back(day_button);
    }
    for (int j = 6; j < 11; ++j)
    {
        Button* day_button = new Button{Point{90, 20 + 40*(j-5)}, 60, 40, std::to_string(j), current_day_cb};
        days.push_back(day_button);
    }
    for (int j = 11; j < 16; ++j)
    {
        Button* day_button = new Button{Point{160, 20 + 40*(j-10)}, 60, 40, std::to_string(j), current_day_cb};
        days.push_back(day_button);
    }
        for (int j = 16; j < 21; ++j)
    {
        Button* day_button = new Button{Point{230, 20 + 40*(j-15)}, 60, 40, std::to_string(j), current_day_cb};
        days.push_back(day_button);
    }
        for (int j = 21; j < 26; ++j)
    {
        Button* day_button = new Button{Point{300, 20 + 40*(j-20)}, 60, 40, std::to_string(j), current_day_cb};
        days.push_back(day_button);
    }
        for (int j = 26; j < 31; ++j)
    {
        Button* day_button = new Button{Point{370, 20 + 40*(j-25)}, 60, 40, std::to_string(j), current_day_cb};
        days.push_back(day_button);
    }
        for (int j = 31; j < 32; ++j)
    {
        Button* day_button = new Button{Point{440, 20 + 40*(j-30)}, 60, 40, std::to_string(j), current_day_cb};
        days.push_back(day_button);
    }
    for (size_t i = 0; i < days.size(); ++i)
    {
        attach(*days[i]);
    }
    attach(main_page_btn);
}

void Month::hide_window()
{
    week_win -> show();
    hide();
}

void Month::main_page_cb(Address, Address pw)
{
    auto& btn = Graph_lib::reference_to<Button>(pw);
    reinterpret_cast<Month&>(btn.window()).hide_window();
}

void Month::current_day_cb(Address, Address pw)
{
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    Day day;
    DayWindow* day_window = new DayWindow(day, 700, 600);
}