#include "year.h"
#include "month.h"

std::vector<std::string> Months_names
{
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};

Year::Year(DateButton* btn, WeekWindow* win, std::string year_number): 
    Window{Point(100,100), 600, 400, year_number},
    year_button{btn},
    week_win {win},
    week_page_btn{Point(x_max() - 100,y_max() - 80), 100, 80, "Back", main_page_cb},
    current_year_text{Point{500, 50}, year_number} 
{
    size_range(BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT);
    for (int j = 0; j < 3; ++j)
    {
        DateButton* month_button = new DateButton{Point{20, 20 + 80*j}, 100, 80, Months_names[j], current_month_cb};
        months.push_back(month_button);
    }
    for (int j = 3; j < 6; ++j)
    {
        DateButton* month_button = new DateButton{Point{130, 20 + 80*(j-3)}, 100, 80, Months_names[j], current_month_cb};
        months.push_back(month_button);
    }
    for (int j = 6; j < 9; ++j)
    {
        DateButton* month_button = new DateButton{Point{240, 20 + 80*(j-6)}, 100, 80, Months_names[j], current_month_cb};
        months.push_back(month_button);
    }
        for (int j = 9; j < 12; ++j)
    {
        DateButton* month_button = new DateButton{Point{350, 20 + 80*(j-9)}, 100, 80, Months_names[j], current_month_cb};
        months.push_back(month_button);
    }
    for (size_t i = 0; i < months.size(); ++i)
    {
        attach(*months[i]);
    }
    current_year_text.set_font_size(20);
    current_year_text.set_color(Color::black);
    attach(current_year_text);
    attach(week_page_btn);
}

Year::~Year()
{
    for (size_t i = 0; i < months.size(); ++i)
    {
        delete months[i];
    }
}

void Year::hide_window()
{
    week_win->set_label("ToDoList");
    week_win->show();
    hide();
}

void Year::current_month(DateButton& btn)
{
    Month* month_window = new Month(&btn, &reinterpret_cast<Year&>(btn.window()), btn.get_label(), year_button->get_label());
    dynamic_cast<Year&&>(btn.window()).hide();
}

void Year::main_page_cb(Address, Address pw)
{
    auto& btn = Graph_lib::reference_to<Button>(pw);
    reinterpret_cast<Year&>(btn.window()).hide_window();
}

void Year::current_month_cb(Address, Address pw)
{
    auto& btn = Graph_lib::reference_to<DateButton>(pw);
    dynamic_cast<Year&&>(btn.window()).current_month(btn);
}
