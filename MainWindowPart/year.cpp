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

Year::Year(Point xy, int h, int w, int year_number): 
    Window{xy, w, h, std::to_string(year_number)}, 
    main_page{Point{0 , y_max()-70}, 100, 70, "Back", main_page_cb}
{
    for (int j = 0; j < 3; ++j)
    {
        Button* month_button = new Button{Point{30, 20 + 110*j}, 80, 60, Months_names[j], [](Address, Address){std::cout << "month" << std::endl;}};
        months.push_back(Month{Months_names[j], month_button});
    }
    for (int j = 3; j < 6; ++j)
    {
        Button* month_button = new Button{Point{30, 20 + 110*j}, 80, 60, Months_names[j], [](Address, Address){std::cout << "month" << std::endl;}};
        months.push_back(Month{Months_names[j], month_button});
    }
    for (int j = 6; j < 9; ++j)
    {
        Button* month_button = new Button{Point{30, 20 + 110*j}, 80, 60, Months_names[j], [](Address, Address){std::cout << "month" << std::endl;}};
        months.push_back(Month{Months_names[j], month_button});
    }
        for (int j = 9; j < 12; ++j)
    {
        Button* month_button = new Button{Point{30, 20 + 110*j}, 80, 60, Months_names[j], [](Address, Address){std::cout << "month" << std::endl;}};
        months.push_back(Month{Months_names[j], month_button});
    }

}

void Year::year()
{
    for (size_t i = 0; i < months.size(); ++i)
    {
        attach(*months[i].month_button);
    }
}

void Year::main_page_back()
{
    hide();
}

void Year::main_page_cb(Address, Address bc)
{
    auto& b = Graph_lib::reference_to<Button>(bc);
    dynamic_cast<Year&>(b.window()).main_page_back();
}

void Year::year_cb(Address, Address ye)
{
    auto& y = Graph_lib::reference_to<Button>(ye);
    dynamic_cast<Year&>(y.window()).year();
}