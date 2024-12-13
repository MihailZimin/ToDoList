//
// Created by Misha on 25.11.2024.
//

#include "TaskWindow.h"

#include <iomanip>

#include "ChangeTaskInfo.h"
#include "PARAMETERS.h"
#include "DayDraw.h"
#include <sstream>

#include "HelpWindow.h"


void TaskWindow::ChangeTaskDetailsCB(Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<TaskWindow&>(btn.window()).ChangeTaskDetails(btn);
}

void TaskWindow::ChangeTaskDetails(MyButton& btn) {
    ChangeTaskInfo* change_task_info = new ChangeTaskInfo(btn, &reinterpret_cast<TaskWindow&>(btn.window()));
    this->hide();
}

void TaskWindow::GoBackCB(Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<TaskWindow&>(btn.window()).GoBack();
}

void TaskWindow::GoBack() {
    this->hide();
    day_window->set_label("Day Window");
    day_window->show();
}

void TaskWindow::DeleteTaskCB(Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<TaskWindow&>(btn.window()).DeleteTask();
}

void TaskWindow::DeleteTask() {
    day_window->removeTask(*(button_from_called.task));
    day_window->redraw();
    this->hide();
    day_window->set_label("Day Window");
    day_window->show();
}



TaskWindow::TaskWindow(MyButton& button_from_called, DayWindow* day_window) :
day_window(day_window), button_from_called(button_from_called),
Window(BASIC_WINDOW_POSITION, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT, "Task"),
txt_info(Graph_lib::Text(Graph_lib::Point{25, 120}, "Info: "+ button_from_called.task->text)),
changeTaskName(MyButton({10, 10}, 80, 30, "Change info",
        button_from_called.task, ChangeTaskDetailsCB)),
go_back(MyButton({0, BASIC_WINDOW_HEIGHT-BUTTON_HEIGHT}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Back", button_from_called.task, GoBackCB)),
delete_task_button(MyButton({BASIC_WINDOW_WIDTH-BUTTON_WIDTH-30, 0}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Delete", button_from_called.task, DeleteTaskCB)),
txt_time_start(Graph_lib::Text(Graph_lib::Point{25, 70}, "")),
txt_time_end(Graph_lib::Text(Graph_lib::Point{25, 90}, ""))
{
    size_range(BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT);

    int hours_start = button_from_called.task->period.start_hour();
    int minutes_start = button_from_called.task->period.start_min();

    int hours_end = button_from_called.task->period.end_hour();
    int minutes_end = button_from_called.task->period.end_min();

    int day_start = button_from_called.task->period.start_date().day();
    int month_start = static_cast<int>(button_from_called.task->period.start_date().month());
    int year_start = button_from_called.task->period.start_date().year();

    int day_end = button_from_called.task->period.end_date().day();
    int month_end = static_cast<int>(button_from_called.task->period.end_date().month());
    int year_end = button_from_called.task->period.end_date().year();


    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << hours_start << ":"
        << std::setw(2) << std::setfill('0') << minutes_start;
    std::string timeString_start = oss.str();

    oss.clear();
    oss.seekp(0);
    oss << std::setw(2) << std::setfill('0') << hours_end << ":"
        << std::setw(2) << std::setfill('0') << minutes_end;
    std::string timeString_end = oss.str();


    std::string time_start = std::to_string(day_start) + '/' + std::to_string(month_start) + '/' + std::to_string(year_start) +
        ": " + timeString_start;
    std::string time_end = std::to_string(day_end) + '/' + std::to_string(month_end) + '/' + std::to_string(year_end) +
        ": " + timeString_end;

    txt_time_start.set_label("Time start: "+ time_start);
    txt_time_end.set_label("Time end: "+ time_end);
    txt_time_start.set_font_size(20);
    txt_time_end.set_font_size(20);
    txt_info.set_font_size(20);

    attach(changeTaskName);
    attach(txt_info);
    attach(txt_time_start);
    attach(txt_time_end);
    attach(go_back);
    attach(delete_task_button);
}



AddTaskWindow::AddTaskWindow(DayWindow* day_window):
Window(BASIC_WINDOW_POSITION, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT, "Add Task Window"),
day_window{day_window},
new_data_button(MyButton({BASIC_WINDOW_WIDTH-BUTTON_WIDTH-30, 0}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Set task", setTaskCB)),
new_name_field(Graph_lib::In_box(Graph_lib::Point(START_BUTTONS_POSITION_X+130, MARGIN),
    BUTTON_WIDTH, BUTTON_HEIGHT-20, "Enter task name:")),
new_info_field(Graph_lib::In_box(Graph_lib::Point(START_BUTTONS_POSITION_X+130, BUTTON_HEIGHT),
    BUTTON_WIDTH, BUTTON_HEIGHT-20, "Details about task:")),
start_time_field(Graph_lib::In_box(Graph_lib::Point(START_BUTTONS_POSITION_X+130, BUTTON_HEIGHT*2-MARGIN),
    BUTTON_WIDTH, BUTTON_HEIGHT-20, "Start time:")),
end_time_field(Graph_lib::In_box(Graph_lib::Point(START_BUTTONS_POSITION_X+130, BUTTON_HEIGHT*3-MARGIN*2),
    BUTTON_WIDTH, BUTTON_HEIGHT-20, "End time:")),
end_day_field(Graph_lib::In_box(Graph_lib::Point(START_BUTTONS_POSITION_X+130, BUTTON_HEIGHT*4-MARGIN*3),
    BUTTON_WIDTH, BUTTON_HEIGHT-20, "Day of end: ")),
end_month_field(Graph_lib::In_box(Graph_lib::Point(START_BUTTONS_POSITION_X+130, BUTTON_HEIGHT*5-MARGIN*4),
    BUTTON_WIDTH, BUTTON_HEIGHT-20, "Month of end: ")),
end_year_field(Graph_lib::In_box(Graph_lib::Point(START_BUTTONS_POSITION_X+130, BUTTON_HEIGHT*6-MARGIN*5),
    BUTTON_WIDTH, BUTTON_HEIGHT-20, "Year of end: ")),
go_back(MyButton({0, BASIC_WINDOW_HEIGHT-BUTTON_HEIGHT}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Back", goBackCB)),
show_help(MyButton({BASIC_WINDOW_WIDTH-BUTTON_WIDTH-30, BUTTON_HEIGHT}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Help", openHelpWindowCB, FL_GREEN))
{
    size_range(BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT);

    attach(new_data_button);
    attach(new_name_field);
    attach(new_info_field);
    attach(start_time_field);
    attach(end_time_field);
    attach(go_back);
    attach(end_day_field);
    attach(end_month_field);
    attach(end_year_field);
    attach(show_help);
}

void AddTaskWindow::openHelpWindowCB(Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<AddTaskWindow&>(btn.window()).openHelpWindow();
}

void AddTaskWindow::openHelpWindow() {
    this->hide();
    HelpAddTaskWindow* help_add_task_window = new HelpAddTaskWindow(this);
}


void AddTaskWindow::setTaskCB(Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<AddTaskWindow&>(btn.window()).setTask();
}

void AddTaskWindow::setTask() {
    std::string name = new_name_field.get_string();
    std::string info = new_info_field.get_string();
    std::string start = start_time_field.get_string();
    std::string end = end_time_field.get_string();
    std::string end_day = end_day_field.get_string();
    std::string end_month = end_month_field.get_string();
    std::string end_year = end_year_field.get_string();

    if (name.empty()) name = "default";
    if (info.empty()) info = "default";

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
        hours_start = START_DEFAULT_HOURS;
        minutes_start = START_DEFAULT_MINUTES;
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
        hours_end = END_DEFAULT_HOURS;
        minutes_end = END_DEFAULT_MINUTES;
    }


    int day_start{day_window->date.day()};
    int month_start{static_cast<int>(day_window->date.month())};
    int year_start{day_window->date.year()};

    int day_end{0};
    int month_end{0};
    int year_end{0};

    try {
        day_end = std::stoi(end_day);
    }
    catch(...) {
        day_end = day_start;
    }
    try {
        month_end = std::stoi(end_month);
    }
    catch(...) {
        month_end = month_start;
    }
    try {
        year_end = std::stoi(end_year);
    }
    catch(...) {
        year_end = day_start;
    }

    if (!is_end_date_greater(day_start, month_start, year_start,
            day_end, month_end, year_end))
    {
        day_end = day_start;
        month_end = month_start;
        year_end = year_start;
    }

    try {
        TaskManager_ns::Task* task = new TaskManager_ns::Task(name, info,
            {hours_start, minutes_start,
                {day_start,
                    day_window->date.month(), year_start},
                hours_end, minutes_end,
                {day_end, static_cast<Chrono_ns::Month>(month_end), year_end}});
        day_window->addTask(task);
        day_window->redraw();
    }

    catch(...) {
        hours_end = END_DEFAULT_HOURS;
        minutes_end = END_DEFAULT_MINUTES;
        hours_start = START_DEFAULT_HOURS;
        minutes_start = START_DEFAULT_MINUTES;
        TaskManager_ns::Task* task = new TaskManager_ns::Task(name, info,
            {hours_start, minutes_start,
                {day_start, day_window->date.month(), year_start},
                hours_end, minutes_end,
                {day_start, day_window->date.month(), year_start}});
        day_window->addTask(task);
        day_window->redraw();
    }
}

void AddTaskWindow::goBackCB(Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<AddTaskWindow&>(btn.window()).goBack();
}

void AddTaskWindow::goBack() {
    std::cout << "went back" << std::endl;
    this->hide();
    day_window->set_label("Day Window");
    day_window->show();
}