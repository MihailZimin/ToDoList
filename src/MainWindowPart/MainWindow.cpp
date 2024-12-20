#include "year.h"
#include <sstream>

extern TaskManager_ns::TaskManager task_manager;

WeekWindow::WeekWindow(Point xy, int h, int w)
    : Window{xy, w, h, "ToDoList"},
    Monday{Point{30,20}, 100, 70, "Monday", cb_day, Chrono_ns::get_week_dates()[0]},
    Tuesday{Point{30, 130}, 100, 70, "Tuesday", cb_day, Chrono_ns::get_week_dates()[1]},
    Wednesday{Point{30,240}, 100, 70, "Wednesday", cb_day, Chrono_ns::get_week_dates()[2]},
    Thursday{Point{140,20}, 100, 70, "Thursday", cb_day, Chrono_ns::get_week_dates()[3]},
    Friday{Point{140,130}, 100, 70, "Friday", cb_day, Chrono_ns::get_week_dates()[4]},
    Saturday{Point{140,240}, 100, 70, "Saturday", cb_day, Chrono_ns::get_week_dates()[5]},
    Sunday{Point{250,20}, 100, 70, "Sunday", cb_day, Chrono_ns::get_week_dates()[6]},
    current_date{Point{10,15}, "today: "},
    next{Point{w - 100 , h/2 - 35}, 100, 70, "years", cb_years},
    prev{Point{0 , y_max()-70}, 100, 70, "Back", cb_back},
    year_page_counter{0},
    week_page_btn{Point{x_max() - 100 , y_max()-70}, 100, 70, "Week page", cb_week_page},
    add_years_btn{Point{x_max() - 100 , y_max()/2 - 35}, 100, 70, "Next", cb_add_years}
{
    size_range(BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT);

    std::cout << current_year << std::endl;
    for (int j = 0; j < 3; ++j)
    {
        DateButton* year = new DateButton{Point{30 + 110*j, 20}, 100, 70, std::to_string(current_year), current_year_cb};
        years[year_page_counter].push_back(year);
        current_year += 1;
    }
    for (int j = 0; j < 3; ++j)
    {
        DateButton* year = new DateButton{Point{30 + 110*j, 130}, 100, 70, std::to_string(current_year), current_year_cb};
        years[year_page_counter].push_back(year);
        current_year += 1;
    }
    for (int j = 0; j < 3; ++j)
    {
        DateButton* year = new DateButton{Point{30 + 110*j, 240}, 100, 70, std::to_string(current_year), current_year_cb};
        years[year_page_counter].push_back(year);
        current_year += 1;
    }

    Chrono_ns::Date today = Chrono_ns::today();
    current_date.set_color(Color::Color_type::black);
    current_date.set_label("today: " 
    + std::to_string(today.day()) 
    + "/" 
    + Chrono_ns::month_to_string(today.month()) 
    + "/" 
    + std::to_string(today.year()));


    colorButton(&Monday, task_manager.get_tasks(Chrono_ns::get_week_dates()[0]).size());
    colorButton(&Tuesday, task_manager.get_tasks(Chrono_ns::get_week_dates()[1]).size());
    colorButton(&Wednesday, task_manager.get_tasks(Chrono_ns::get_week_dates()[2]).size());
    colorButton(&Thursday, task_manager.get_tasks(Chrono_ns::get_week_dates()[3]).size());
    colorButton(&Friday, task_manager.get_tasks(Chrono_ns::get_week_dates()[4]).size());
    colorButton(&Saturday, task_manager.get_tasks(Chrono_ns::get_week_dates()[5]).size());
    colorButton(&Sunday, task_manager.get_tasks(Chrono_ns::get_week_dates()[6]).size());
    Monday.label = "Monday " + std::to_string(task_manager.get_tasks(Chrono_ns::get_week_dates()[0]).size());
    Tuesday.label = "Tuesday " + std::to_string(task_manager.get_tasks(Chrono_ns::get_week_dates()[1]).size());
    Wednesday.label = "Wednesday " + std::to_string(task_manager.get_tasks(Chrono_ns::get_week_dates()[2]).size());
    Thursday.label = "Thursday " + std::to_string(task_manager.get_tasks(Chrono_ns::get_week_dates()[3]).size());
    Friday.label = "Friday " + std::to_string(task_manager.get_tasks(Chrono_ns::get_week_dates()[4]).size());
    Saturday.label = "Saturday " + std::to_string(task_manager.get_tasks(Chrono_ns::get_week_dates()[5]).size());
    Sunday.label = "Sunday " + std::to_string(task_manager.get_tasks(Chrono_ns::get_week_dates()[6]).size());

    attach(Monday);
    attach(Tuesday);
    attach(Wednesday);
    attach(Thursday);
    attach(Friday);
    attach(Saturday);
    attach(Sunday);
    attach(current_date);
    attach(next);
};

WeekWindow::~WeekWindow()
{
    for (size_t i = 0; i < years.size(); ++i) 
    {
        for (size_t j = 0; j < years[i].size(); ++j) { delete years[i][j]; }
    }
};

void WeekWindow::week_page()
{
    for (size_t i = 0; i < years[year_page_counter].size(); ++i)
    {
        detach(*years[year_page_counter][i]);
    }
    if (year_page_counter != 0)
    {
        detach(prev);
    }
    if (year_page_counter != 5)
    {
        detach(add_years_btn);
    }

    year_page_counter = 0;

    attach(Monday);
    attach(Tuesday);
    attach(Wednesday);
    attach(Thursday);
    attach(Friday);
    attach(Saturday);
    attach(Sunday);
    attach(current_date);
    attach(next);

    redraw();
}

void WeekWindow::add_years()
{
    if (year_page_counter == 0)
    {
        attach(prev);
    }
    for (size_t i = 0; i < years[year_page_counter].size(); ++i)
    {
        detach(*years[year_page_counter][i]);                  
    }

    year_page_counter += 1;

    if (year_page_counter == 5)
    {
        detach(add_years_btn);
    }

    if (year_page_counter < years.size())
    {
        for (size_t i = 0; i < years[year_page_counter].size(); ++i)
        {
            attach(*years[year_page_counter][i]);                  
        }
        redraw();  
    }
    else
    {
        years.resize(year_page_counter + 1);

        for (int j = 0; j < 3; ++j)
        {
            DateButton* year = new DateButton{Point{30 + 110*j, 20}, 100, 70, std::to_string(current_year), current_year_cb};
            years[year_page_counter].push_back(year);
            current_year += 1;
        }
        for (int j = 0; j < 3; ++j)
        {
            DateButton* year = new DateButton{Point{30 + 110*j, 130}, 100, 70, std::to_string(current_year), current_year_cb};
            years[year_page_counter].push_back(year);
            current_year += 1;
        }
        for (int j = 0; j < 3; ++j)
        {
            DateButton* year = new DateButton{Point{30 + 110*j, 240}, 100, 70, std::to_string(current_year), current_year_cb};
            years[year_page_counter].push_back(year);
            current_year += 1;
        }
        for (size_t i = 0; i < years[year_page_counter].size(); ++i)
        {
            attach(*years[year_page_counter][i]);                  
        }
        redraw();
    }
}

void WeekWindow::back_page()
{
    if (year_page_counter == 5)
    {
        attach(add_years_btn);
    }
    for (size_t i = 0; i < years[year_page_counter].size(); ++i)
    {
        detach(*years[year_page_counter][i]);                  
    }
    if (year_page_counter == 1)
    {
        year_page_counter -= 1;
        for (size_t i = 0; i < years[year_page_counter].size(); ++i)
        {
            attach(*years[year_page_counter][i]); 
        }
        detach(prev);
        redraw();
    }
    else
    {
        year_page_counter -= 1;
        for (size_t i = 0; i < years[year_page_counter].size(); ++i)
        {
            attach(*years[year_page_counter][i]); 
        }
        redraw();
    }
}

void WeekWindow::years_page()
{
    detach(Monday);
    detach(Tuesday);
    detach(Wednesday);
    detach(Thursday);
    detach(Friday);
    detach(Saturday);
    detach(Sunday);
    detach(current_date);
    detach(next);

    attach(add_years_btn);
    attach(week_page_btn);             

    for (size_t i = 0; i < years[year_page_counter].size(); ++i)                
    {
        attach(*years[year_page_counter][i]);
    }

    redraw();
}

void WeekWindow::cb_years(Address, Address years)
{
    auto& cy = Graph_lib::reference_to<Button>(years);
    dynamic_cast<WeekWindow&>(cy.window()).years_page();
}

void WeekWindow::cb_add_years(Address, Address add)
{
    auto& ca = Graph_lib::reference_to<Button>(add);
    dynamic_cast<WeekWindow&>(ca.window()).add_years();
}

void WeekWindow::cb_week_page(Address, Address week)
{
    auto& we = Graph_lib::reference_to<Button>(week);
    dynamic_cast<WeekWindow&>(we.window()).week_page();
}

void WeekWindow::cb_back(Address, Address back)
{
    auto& ba = Graph_lib::reference_to<Button>(back);
    dynamic_cast<WeekWindow&>(ba.window()).back_page();
}

void WeekWindow::current_year_cb(Address, Address pw)
{
    auto& btn = Graph_lib::reference_to<DateButton>(pw);
    reinterpret_cast<WeekWindow&>(btn.window()).show_current_year(btn);
}

void WeekWindow::cb_day(Address, Address pw)
{
    auto& btn = Graph_lib::reference_to<DateButton>(pw);
    reinterpret_cast<WeekWindow&>(btn.window()).show_day(btn);
}

void WeekWindow::show_day(DateButton& btn) {
    std::string lab = btn.get_label();
    std::istringstream iss(lab);
    std::string real_name;
    iss >> real_name;
    DayWindow* day_window = new DayWindow(Graph_lib::Point{this->x(), this->y()}, 600, 400, btn.date,  real_name, &btn);
    day_window->week_window = this;
    this->hide();
}

void WeekWindow::show_current_year(DateButton& btn)
{
    Year* year_window = new Year(Graph_lib::Point{this->x(), this->y()}, &btn, &reinterpret_cast<WeekWindow&>(btn.window()), btn.get_label());
    this->hide();
}