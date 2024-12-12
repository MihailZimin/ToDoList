//
// Created by Misha on 25.11.2024.
//

#include "ChangeTaskInfo.h"

#include <DayWork/DayDraw.h>
#include <sstream>

#include "PARAMETERS.h"
#include "TaskWindow.h"

bool is_end_date_greater(int start_day, int start_month, int start_year, int end_day, int end_month, int end_year) {

    if (end_year > start_year) return true;
    if (end_year < start_year) return false;

    if (end_month > start_month) return true;
    if (end_month < start_month) return false;

    return end_day > start_day;
}

void ChangeTaskInfo::changeTaskCB(Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<ChangeTaskInfo&>(btn.window()).changeTask(*btn.task);
}

void ChangeTaskInfo::GoBackCB(Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<ChangeTaskInfo&>(btn.window()).goBack();
}


void ChangeTaskInfo::goBack() {
    std::cout << "went back" << std::endl;
    this->hide();
}



ChangeTaskInfo::ChangeTaskInfo(MyButton* button, TaskWindow* taskWindow):
Window(BASIC_WINDOW_POSITION, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT, "Change Window"),
task_window(taskWindow),
new_name_field(new Graph_lib::In_box(Graph_lib::Point(FIELDS_START_POSITION_X, FIELDS_START_POSITION_Y),
    FIELD_WIDTH, FIELD_HEIGHT, "Enter new name:")),
new_text_field(new Graph_lib::In_box(Graph_lib::Point(FIELDS_START_POSITION_X, FIELDS_START_POSITION_Y+FIELD_HEIGHT),
    FIELD_WIDTH, FIELD_HEIGHT, "Enter new information:")),
new_start_time_field(new Graph_lib::In_box(Graph_lib::Point(FIELDS_START_POSITION_X, FIELDS_START_POSITION_Y+2*FIELD_HEIGHT),
    FIELD_WIDTH, FIELD_HEIGHT, "Enter new start time:")),
new_end_time_field(new Graph_lib::In_box(Graph_lib::Point(FIELDS_START_POSITION_X, FIELDS_START_POSITION_Y+3*FIELD_HEIGHT),
    FIELD_WIDTH, FIELD_HEIGHT, "Enter new end time:")),
new_end_day_field(new Graph_lib::In_box(Graph_lib::Point(FIELDS_START_POSITION_X, FIELDS_START_POSITION_Y+4*FIELD_HEIGHT),
    FIELD_WIDTH, FIELD_HEIGHT, "Enter day end:")),
new_end_month_field(new Graph_lib::In_box(Graph_lib::Point(FIELDS_START_POSITION_X, FIELDS_START_POSITION_Y+5*FIELD_HEIGHT),
    FIELD_WIDTH, FIELD_HEIGHT, "Enter month end:")),
new_end_year_field(new Graph_lib::In_box(Graph_lib::Point(FIELDS_START_POSITION_X, FIELDS_START_POSITION_Y+6*FIELD_HEIGHT),
    FIELD_WIDTH, FIELD_HEIGHT, "Enter year end:")),
new_info_button(new MyButton({BASIC_WINDOW_WIDTH-BUTTON_WIDTH, 0}, BUTTON_WIDTH, BUTTON_HEIGHT,
    "Change", button->task, changeTaskCB)),
go_back(new MyButton({0, BASIC_WINDOW_HEIGHT-BUTTON_HEIGHT}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Back", button->task, GoBackCB)),
Note0_0(new Graph_lib::Text(Graph_lib::Point{MARGIN, BASIC_WINDOW_HEIGHT-MARGIN*5}, NOTE0_0))
{
    size_range(BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT);

    attach(*new_name_field);
    attach(*new_text_field);
    attach(*new_start_time_field);
    attach(*new_end_time_field);
    attach(*new_end_day_field);
    attach(*new_end_month_field);
    attach(*new_end_year_field);
    attach(*new_info_button);
    attach(*go_back);
    attach(*Note0_0);
}

void ChangeTaskInfo::changeTask(TaskManager_ns::Task& task) {
    std::string name = new_name_field->get_string();
    std::string text = new_text_field->get_string();
    std::string start = new_start_time_field->get_string();
    std::string end = new_end_time_field->get_string();
    std::string end_day = new_end_day_field->get_string();
    std::string end_month = new_end_month_field->get_string();
    std::string end_year = new_end_year_field->get_string();

    if (name.empty()) name = task.name;
    if (text.empty()) text = task.text;

    int hours_start{INVALID_TIME}, minutes_start{INVALID_TIME};

    try {
        size_t colonPos = start.find(':');

        hours_start = std::stoi(start.substr(0, colonPos));
        minutes_start = std::stoi(start.substr(colonPos + 1));
        if (hours_start < 0 || hours_start >= 24 || minutes_start < 0 || minutes_start >= 60) {
            hours_start = START_DEFAULT_HOURS;
            minutes_start = START_DEFAULT_MINUTES;
        }
    }
    catch (...) {
        hours_start = task.period.start_hour();
        minutes_start = task.period.start_min();
    }

    int hours_end{INVALID_TIME}, minutes_end{INVALID_TIME};

    try {
        size_t colonPos = end.find(':');

        hours_end = std::stoi(end.substr(0, colonPos));
        minutes_end = std::stoi(end.substr(colonPos + 1));
        if (hours_end < 0 || hours_end >= 24 || minutes_end < 0 || minutes_end >= 60) {
            hours_end = END_DEFAULT_HOURS;
            minutes_end = END_DEFAULT_MINUTES;
        }
    }
    catch(...) {
        hours_end = task.period.end_hour();
        minutes_end = task.period.end_min();
    }


    int day_start = task_window->day_window->date.day();
    int month_start = static_cast<int>(task_window->day_window->date.month());
    int year_start = task_window->day_window->date.year();

    int day_end_current = task.period.end_date().day();
    int month_end_current = static_cast<int>(task.period.end_date().month());
    int year_end_current = task.period.end_date().year();

    int day_end{0};
    int month_end{0};
    int year_end{0};

    try {
        month_end = std::stoi(end_month);
    }
    catch(...) {
        month_end = month_end_current;
    }
    try {
        year_end = std::stoi(end_year);
    }
    catch(...) {
        year_end = year_end_current;
    }
    try {
        day_end = std::stoi(end_day);
    }
    catch(...) {
        day_end = day_end_current;
    }

    if (!is_end_date_greater(day_start, month_start, year_start,
        day_end, month_end, year_end)) {
        day_end = day_end_current;
        month_end = month_end_current;
        year_end = year_end_current;
    }

    task_window->day_window->removeTask(task);

    try {
        Chrono_ns::Period p = {hours_start, minutes_start,
                {task.period.start_date()},
                hours_end, minutes_end,
                {day_end, static_cast<Chrono_ns::Month>(month_end), year_end}};
        task.name = name;
        task.text = text;
        task.period = p;
        task_window->day_window->addTask(&task);
        task_window->day_window->redraw();
        task_window->redraw();
    }
    catch(...) {
        hours_end = END_DEFAULT_HOURS;
        minutes_end = END_DEFAULT_MINUTES;
        hours_start = START_DEFAULT_HOURS;
        minutes_start = START_DEFAULT_MINUTES;
        Chrono_ns::Period p = {hours_start, minutes_start,
                task.period.start_date(), hours_end, minutes_end,
                {task.period.end_date()}};
        task.name = name;
        task.text = text;
        task.period = p;
        task_window->day_window->addTask(&task);
        task_window->day_window->redraw();
        task_window->redraw();
    }
}

ChangeTaskInfo::~ChangeTaskInfo() {
    std::cout << "Destructor ChangeTaskInfo" << std::endl;
    delete new_name_field;
    delete new_text_field;
    delete new_start_time_field;
    delete new_end_time_field;
    delete new_end_day_field;
    delete new_end_month_field;
    delete new_end_year_field;
    delete go_back;
}