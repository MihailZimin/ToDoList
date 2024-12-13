//
// Created by Misha on 25.11.2024.
//

#include "ChangeTaskInfo.h"

#include <DayWork/DayDraw.h>
#include <sstream>

#include "HelpWindow.h"
#include "PARAMETERS.h"
#include "TaskWindow.h"

bool is_end_date_greater(int start_day, int start_month, int start_year, int end_day, int end_month, int end_year) {

    if (end_year > start_year) return true;
    if (end_year < start_year) return false;

    if (end_month > start_month) return true;
    if (end_month < start_month) return false;

    return end_day >= start_day;
}

void WindowTaskChanger::changeTaskCB(Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    if (btn.task == nullptr) {
        reinterpret_cast<WindowTaskChanger&>(btn.window()).setTask();
    }
    reinterpret_cast<WindowTaskChanger&>(btn.window()).changeTask(*btn.task);
}

void WindowTaskChanger::goBackCB(Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<WindowTaskChanger&>(btn.window()).goBack();
}

void WindowTaskChanger::openHelpWindowCB(Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<WindowTaskChanger&>(btn.window()).openHelpWindow();
}


WindowTaskChanger::WindowTaskChanger(const MyButton& button_from_called) :
Window(BASIC_WINDOW_POSITION, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT, ""),
new_name_field(MyIn_box(Graph_lib::Point(FIELDS_START_POSITION_X, FIELDS_START_POSITION_Y),
    FIELD_WIDTH, FIELD_HEIGHT, "Enter new name:")),
new_text_field(MyIn_box(Graph_lib::Point(FIELDS_START_POSITION_X, FIELDS_START_POSITION_Y+FIELD_HEIGHT),
    FIELD_WIDTH, FIELD_HEIGHT, "Enter new information:")),
new_start_time_field(MyIn_box(Graph_lib::Point(FIELDS_START_POSITION_X, FIELDS_START_POSITION_Y+2*FIELD_HEIGHT),
    FIELD_WIDTH, FIELD_HEIGHT, "Enter new start time:")),
new_end_time_field(MyIn_box(Graph_lib::Point(FIELDS_START_POSITION_X, FIELDS_START_POSITION_Y+3*FIELD_HEIGHT),
    FIELD_WIDTH, FIELD_HEIGHT, "Enter new end time:")),
new_end_day_field(MyIn_box(Graph_lib::Point(FIELDS_START_POSITION_X, FIELDS_START_POSITION_Y+4*FIELD_HEIGHT),
    FIELD_WIDTH, FIELD_HEIGHT, "Enter day end:")),
new_end_month_field(MyIn_box(Graph_lib::Point(FIELDS_START_POSITION_X, FIELDS_START_POSITION_Y+5*FIELD_HEIGHT),
    FIELD_WIDTH, FIELD_HEIGHT, "Enter month end:")),
new_end_year_field(MyIn_box(Graph_lib::Point(FIELDS_START_POSITION_X, FIELDS_START_POSITION_Y+6*FIELD_HEIGHT),
    FIELD_WIDTH, FIELD_HEIGHT, "Enter year end:")),
new_info_button(MyButton({BASIC_WINDOW_WIDTH-BUTTON_WIDTH, 0}, BUTTON_WIDTH, BUTTON_HEIGHT,
    "Change", button_from_called.task, changeTaskCB)),
go_back(MyButton({0, BASIC_WINDOW_HEIGHT-BUTTON_HEIGHT}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Back", button_from_called.task, goBackCB)),
show_help(MyButton({BASIC_WINDOW_WIDTH-BUTTON_WIDTH, BUTTON_HEIGHT}, BUTTON_WIDTH, BUTTON_HEIGHT,
    "Help", button_from_called.task, openHelpWindowCB, FL_GREEN))
{
    size_range(BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT);

    set_label("Change task");

    attach(new_name_field);
    attach(new_text_field);
    attach(new_start_time_field);
    attach(new_end_time_field);
    attach(new_end_day_field);
    attach(new_end_month_field);
    attach(new_end_year_field);
    attach(new_info_button);
    attach(go_back);
    attach(show_help);
}

WindowTaskChanger::WindowTaskChanger() :
Window(BASIC_WINDOW_POSITION, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT, ""),
new_name_field(MyIn_box(Graph_lib::Point(FIELDS_START_POSITION_X, FIELDS_START_POSITION_Y),
    FIELD_WIDTH, FIELD_HEIGHT, "Enter new name:")),
new_text_field(MyIn_box(Graph_lib::Point(FIELDS_START_POSITION_X, FIELDS_START_POSITION_Y+FIELD_HEIGHT),
    FIELD_WIDTH, FIELD_HEIGHT, "Enter new information:")),
new_start_time_field(MyIn_box(Graph_lib::Point(FIELDS_START_POSITION_X, FIELDS_START_POSITION_Y+2*FIELD_HEIGHT),
    FIELD_WIDTH, FIELD_HEIGHT, "Enter new start time:")),
new_end_time_field(MyIn_box(Graph_lib::Point(FIELDS_START_POSITION_X, FIELDS_START_POSITION_Y+3*FIELD_HEIGHT),
    FIELD_WIDTH, FIELD_HEIGHT, "Enter new end time:")),
new_end_day_field(MyIn_box(Graph_lib::Point(FIELDS_START_POSITION_X, FIELDS_START_POSITION_Y+4*FIELD_HEIGHT),
    FIELD_WIDTH, FIELD_HEIGHT, "Enter day end:")),
new_end_month_field(MyIn_box(Graph_lib::Point(FIELDS_START_POSITION_X, FIELDS_START_POSITION_Y+5*FIELD_HEIGHT),
    FIELD_WIDTH, FIELD_HEIGHT, "Enter month end:")),
new_end_year_field(MyIn_box(Graph_lib::Point(FIELDS_START_POSITION_X, FIELDS_START_POSITION_Y+6*FIELD_HEIGHT),
    FIELD_WIDTH, FIELD_HEIGHT, "Enter year end:")),
new_info_button(MyButton({BASIC_WINDOW_WIDTH-BUTTON_WIDTH, 0}, BUTTON_WIDTH, BUTTON_HEIGHT,
    "Set task", changeTaskCB)),
go_back(MyButton({0, BASIC_WINDOW_HEIGHT-BUTTON_HEIGHT}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Back", goBackCB)),
show_help(MyButton({BASIC_WINDOW_WIDTH-BUTTON_WIDTH, BUTTON_HEIGHT}, BUTTON_WIDTH, BUTTON_HEIGHT,
    "Help", openHelpWindowCB, FL_GREEN))
{
    size_range(BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT);

    set_label("Add task");

    attach(new_name_field);
    attach(new_text_field);
    attach(new_start_time_field);
    attach(new_end_time_field);
    attach(new_end_day_field);
    attach(new_end_month_field);
    attach(new_end_year_field);
    attach(new_info_button);
    attach(go_back);
    attach(show_help);
}


void ChangeTaskInfo::goBack() {
    this->hide();
    task_window->day_window->set_label("Day Window");
    task_window->day_window->show();
}

void ChangeTaskInfo::openHelpWindow() {
    this->hide();
    HelpChangeTaskWindow* help_change_task_window = new HelpChangeTaskWindow(this);
}

ChangeTaskInfo::ChangeTaskInfo(MyButton& button_from_called, TaskWindow* task_window):
    WindowTaskChanger(button_from_called),
    task_window(task_window), button_from_called(button_from_called){}


void WindowTaskChanger::reattachFields(const Information& info) {
    detach(new_name_field);
    detach(new_text_field);
    detach(new_start_time_field);
    detach(new_end_time_field);
    detach(new_end_day_field);
    detach(new_end_month_field);
    detach(new_end_year_field);

    new_name_field.set_inside_text(info.name);
    new_text_field.set_inside_text(info.text);
    new_start_time_field.set_inside_text(info.start);
    new_end_time_field.set_inside_text(info.end);
    new_end_day_field.set_inside_text(info.end_day);
    new_end_month_field.set_inside_text(info.end_month);
    new_end_year_field.set_inside_text(info.end_year);

    attach(new_name_field);
    attach(new_text_field);
    attach(new_start_time_field);
    attach(new_end_time_field);
    attach(new_end_day_field);
    attach(new_end_month_field);
    attach(new_end_year_field);
}


void WindowTaskChanger::setColor(Fl_Color color) {
    new_name_field.color(color);
    new_text_field.color(color);
    new_start_time_field.color(color);
    new_end_time_field.color(color);
    new_end_day_field.color(color);
    new_end_month_field.color(color);
    new_end_year_field.color(color);
}

void WindowTaskChanger::setPeriodColor(Fl_Color color) {
    new_start_time_field.color(color);
    new_end_time_field.color(color);
    new_end_day_field.color(color);
    new_end_month_field.color(color);
    new_end_year_field.color(color);
}

Information WindowTaskChanger::processData() {
    Information info;
    info.name = new_name_field.get_string();
    info.text = new_text_field.get_string();
    info.start = new_start_time_field.get_string();
    info.end = new_end_time_field.get_string();
    info.end_day = new_end_day_field.get_string();
    info.end_month = new_end_month_field.get_string();
    info.end_year = new_end_year_field.get_string();

    return info;
}

void WindowTaskChanger::checkDefaultStates(Information& info) {}

void ChangeTaskInfo::changeTask(TaskManager_ns::Task& task) {
    setColor(DEFAULT_COLOR);
    Information info = processData();


    int day_end_current = task.period.end_date().day();
    int month_end_current = static_cast<int>(task.period.end_date().month());
    int year_end_current = task.period.end_date().year();

    if (info.name.empty()) {
        info.name = task.name;
        new_name_field.color(FL_RED);
    }
    if (info.text.empty()) {
        info.text = task.text;
        new_text_field.color(FL_RED);
    }
    if (info.start.empty()) {
        info.start = "00:00";
        new_start_time_field.color(FL_RED);
    }
    if (info.end.empty()) {
        info.end = "23:59";
        new_end_time_field.color(FL_RED);
    }
    if (info.end_day.empty()) {
        info.end_day = std::to_string(day_end_current);
        new_end_day_field.color(FL_RED);
    }
    if (info.end_month.empty()) {
        info.end_month = std::to_string(month_end_current);
        new_end_month_field.color(FL_RED);
    }
    if (info.end_year.empty()) {
        info.end_year = std::to_string(year_end_current);
        new_end_year_field.color(FL_RED);
    }

    int hours_start{INVALID_TIME}, minutes_start{INVALID_TIME};

    try {
        size_t colonPos = info.start.find(':');

        hours_start = std::stoi(info.start.substr(0, colonPos));
        minutes_start = std::stoi(info.start.substr(colonPos + 1));
        if (hours_start < 0 || hours_start >= 24 || minutes_start < 0 || minutes_start >= 60) {
            new_start_time_field.color(FL_RED);
            hours_start = START_DEFAULT_HOURS;
            minutes_start = START_DEFAULT_MINUTES;
        }
    }
    catch (...) {
        new_start_time_field.color(FL_RED);
        hours_start = task.period.start_hour();
        minutes_start = task.period.start_min();
    }

    int hours_end{INVALID_TIME}, minutes_end{INVALID_TIME};

    try {
        size_t colonPos = info.end.find(':');

        hours_end = std::stoi(info.end.substr(0, colonPos));
        minutes_end = std::stoi(info.end.substr(colonPos + 1));
        if (hours_end < 0 || hours_end >= 24 || minutes_end < 0 || minutes_end >= 60) {
            new_end_time_field.color(FL_RED);
            hours_end = END_DEFAULT_HOURS;
            minutes_end = END_DEFAULT_MINUTES;
        }
    }
    catch(...) {
        new_end_time_field.color(FL_RED);
        hours_end = task.period.end_hour();
        minutes_end = task.period.end_min();
    }


    int day_start = task_window->day_window->date.day();
    int month_start = static_cast<int>(task_window->day_window->date.month());
    int year_start = task_window->day_window->date.year();


    int day_end{0};
    int month_end{0};
    int year_end{0};

    try {
        day_end = std::stoi(info.end_day);
    }
    catch(...) {
        new_end_day_field.color(FL_RED);
        day_end = day_end_current;
    }
    try {
        month_end = std::stoi(info.end_month);
    }
    catch(...) {
        new_end_month_field.color(FL_RED);
        month_end = month_end_current;
    }
    try {
        year_end = std::stoi(info.end_year);
    }
    catch(...) {
        new_end_year_field.color(FL_RED);
        year_end = year_end_current;
    }

    if (!is_end_date_greater(day_start, month_start, year_start,
        day_end, month_end, year_end)) {
        new_end_day_field.color(FL_RED);
        new_end_month_field.color(FL_RED);
        new_end_year_field.color(FL_RED);
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
        task.name = info.name;
        task.text = info.text;
        task.period = p;
        task_window->day_window->addTask(&task);
    }
    catch(...) {
        hours_end = END_DEFAULT_HOURS;
        minutes_end = END_DEFAULT_MINUTES;
        hours_start = START_DEFAULT_HOURS;
        minutes_start = START_DEFAULT_MINUTES;
        setPeriodColor(FL_RED);
        Chrono_ns::Period p = {hours_start, minutes_start,
                task.period.start_date(), hours_end, minutes_end,
                {task.period.end_date()}};
        task.name = info.name;
        task.text = info.text;
        task.period = p;
        task_window->day_window->addTask(&task);
    }
    task_window->day_window->redraw();
    task_window->redraw();
    reattachFields(info);
}



AddTaskWindow::AddTaskWindow(DayWindow* day_window):
    WindowTaskChanger(),
    day_window{day_window} {

}

void AddTaskWindow::openHelpWindow() {
    this->hide();
    HelpAddTaskWindow* help_add_task_window = new HelpAddTaskWindow(this);
}

void AddTaskWindow::goBack() {
    std::cout << "went back" << std::endl;
    this->hide();
    day_window->set_label("Day Window");
    day_window->show();
}

void AddTaskWindow::setTask() {
    setColor(DEFAULT_COLOR);
    Information info = processData();

    int day_start{day_window->date.day()};
    int month_start{static_cast<int>(day_window->date.month())};
    int year_start{day_window->date.year()};

    if (info.name.empty()) {
        info.name = "default";
        new_name_field.color(FL_RED);
    }
    if (info.text.empty()) {
        info.text = "default";
        new_text_field.color(FL_RED);
    }
    if (info.start.empty()) {
        info.start = "00:00";
        new_start_time_field.color(FL_RED);
    }
    if (info.end.empty()) {
        info.end = "23:59";
        new_end_time_field.color(FL_RED);
    }
    if (info.end_day.empty()) {
        info.end_day = std::to_string(day_start);
        new_end_day_field.color(FL_RED);
    }
    if (info.end_month.empty()) {
        info.end_month = std::to_string(month_start);
        new_end_month_field.color(FL_RED);
    }
    if (info.end_year.empty()) {
        info.end_year = std::to_string(year_start);
        new_end_year_field.color(FL_RED);
    }


    int hours_start{INVALID_TIME}, minutes_start{INVALID_TIME};

    try {
        size_t colonPos = info.start.find(':');

        hours_start = std::stoi(info.start.substr(0, colonPos));
        minutes_start = std::stoi(info.start.substr(colonPos + 1));
        if (hours_start < 0 || hours_start >= 24 || minutes_start < 0 || minutes_start >= 60) {
            hours_start = START_DEFAULT_HOURS;
            minutes_start = START_DEFAULT_MINUTES;
            new_start_time_field.color(FL_RED);
        }
    }
    catch (...) {
        hours_start = START_DEFAULT_HOURS;
        minutes_start = START_DEFAULT_MINUTES;
        new_start_time_field.color(FL_RED);
    }

    int hours_end{INVALID_TIME}, minutes_end{INVALID_TIME};

    try {
        size_t colonPos = info.end.find(':');

        hours_end = std::stoi(info.end.substr(0, colonPos));
        minutes_end = std::stoi(info.end.substr(colonPos + 1));
        if (hours_end < 0 || hours_end >= 24 || minutes_end < 0 || minutes_end >= 60) {
            hours_end = END_DEFAULT_HOURS;
            minutes_end = END_DEFAULT_MINUTES;
            new_end_time_field.color(FL_RED);
        }
    }
    catch(...) {
        hours_end = END_DEFAULT_HOURS;
        minutes_end = END_DEFAULT_MINUTES;
        new_end_time_field.color(FL_RED);
    }

    int day_end{0};
    int month_end{0};
    int year_end{0};

    try {
        day_end = std::stoi(info.end_day);
    }
    catch(...) {
        day_end = day_start;
        new_end_day_field.color(FL_RED);
    }
    try {
        month_end = std::stoi(info.end_month);
    }
    catch(...) {
        month_end = month_start;
        new_end_month_field.color(FL_RED);
    }
    try {
        year_end = std::stoi(info.end_year);
    }
    catch(...) {
        year_end = day_start;
        new_end_year_field.color(FL_RED);
    }

    if (!is_end_date_greater(day_start, month_start, year_start,
            day_end, month_end, year_end))
    {
        day_end = day_start;
        month_end = month_start;
        year_end = year_start;
        new_end_day_field.color(FL_RED);
        new_end_month_field.color(FL_RED);
        new_end_year_field.color(FL_RED);
    }

    try {
        TaskManager_ns::Task* task = new TaskManager_ns::Task(info.name, info.text,
            {hours_start, minutes_start,
                {day_start,
                    day_window->date.month(), year_start},
                hours_end, minutes_end,
                {day_end, static_cast<Chrono_ns::Month>(month_end), year_end}});
        day_window->addTask(task);
    }

    catch(...) {
        hours_end = END_DEFAULT_HOURS;
        minutes_end = END_DEFAULT_MINUTES;
        hours_start = START_DEFAULT_HOURS;
        minutes_start = START_DEFAULT_MINUTES;
        setPeriodColor(FL_RED);
        TaskManager_ns::Task* task = new TaskManager_ns::Task(info.name, info.text,
            {hours_start, minutes_start,
                {day_start, day_window->date.month(), year_start},
                hours_end, minutes_end,
                {day_start, day_window->date.month(), year_start}});
        day_window->addTask(task);
    }
    day_window->redraw();
    reattachFields(info);
}