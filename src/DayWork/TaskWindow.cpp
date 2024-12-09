//
// Created by Misha on 25.11.2024.
//

#include "TaskWindow.h"

#include <iomanip>

#include "ChangeTaskInfo.h"
#include "PARAMETERS.h"
#include "DayDraw.h"
#include <sstream>


void TaskWindow::ChangeTaskNameCB(Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<TaskWindow&>(btn.window()).ChangeTaskName(btn);
}

void TaskWindow::ChangeTaskName(MyButton& btn) {
    ChangeTaskInfo* changeNameWin = new ChangeTaskInfo(&btn, &reinterpret_cast<TaskWindow&>(btn.window()));
    this->need_to_be_destroyed = false;
    this->hide();
}

void TaskWindow::GoBackCB(Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<TaskWindow&>(btn.window()).goBack();
}

void TaskWindow::goBack() {
    std::cout << "went back" << std::endl;
    this->need_to_be_destroyed = true;
    this->hide();
}

void TaskWindow::DeleteTaskCB(Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<TaskWindow&>(btn.window()).deleteTask();
}

void TaskWindow::deleteTask() {
    day_window->removeTask(*button->task);
    day_window->redraw();
    this->need_to_be_destroyed = true;
    this->hide();
}


TaskWindow::TaskWindow(MyButton* button, DayWindow* day_window) :
day_window(day_window), button(button),
Graph_lib::Window(BASIC_WINDOW_POSITION, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT, "Task"),
txt_info(new Graph_lib::Text(Graph_lib::Point{25, 120}, "Info: "+ button->task->text)),
changeTaskName(new MyButton({10, 10}, 80, 30, "Change info",
        button->task, ChangeTaskNameCB)),
go_back(new MyButton({0, BASIC_WINDOW_HEIGHT-BUTTON_HEIGHT}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Back", button->task, GoBackCB)),
delete_task_button(new MyButton({BASIC_WINDOW_WIDTH-BUTTON_WIDTH-30, 0}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Delete", button->task, DeleteTaskCB)) {
    unsigned hours_start = button->task->period.start_hour();
    unsigned minutes_start = button->task->period.start_min();
    unsigned hours_end = button->task->period.end_hour();
    unsigned minutes_end = button->task->period.end_min();
    unsigned day_start = static_cast<unsigned>(button->task->period.start_date().day());
    unsigned month_start = static_cast<unsigned>(button->task->period.start_date().month());
    unsigned year_start = static_cast<unsigned>(button->task->period.start_date().year());
    unsigned day_end = static_cast<unsigned>(button->task->period.end_date().day());
    unsigned month_end = static_cast<unsigned>(button->task->period.end_date().month());
    unsigned year_end = static_cast<unsigned>(button->task->period.end_date().year());


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
    txt_time_start = new Graph_lib::Text(Graph_lib::Point{25, 70}, "Time start: "+ time_start);
    txt_time_end = new Graph_lib::Text(Graph_lib::Point{25, 90}, "Time end: "+ time_end);
    txt_time_start->set_font_size(20);
    txt_time_end->set_font_size(20);
    txt_info->set_font_size(20);
    attach(*changeTaskName);
    attach(*txt_info);
    attach(*txt_time_start);
    attach(*txt_time_end);
    attach(*go_back);
    attach(*delete_task_button);
}



AddTaskWindow::AddTaskWindow(MyButton *button, DayWindow *day_window):
Graph_lib::Window(BASIC_WINDOW_POSITION, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT, "Add Task Window"),
day_window{day_window},
new_data_button(new MyButton({START_BUTTONS_POSITION_X+220, 10}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Set task", button->task, SetTaskCB)),
new_name_field(new Graph_lib::In_box(Graph_lib::Point(START_BUTTONS_POSITION_X+130, MARGIN),
    BUTTON_WIDTH, BUTTON_HEIGHT-20, "Enter task name:")),
new_info_field(new Graph_lib::In_box(Graph_lib::Point(START_BUTTONS_POSITION_X+130, BUTTON_HEIGHT),
    BUTTON_WIDTH, BUTTON_HEIGHT-20, "Information about task:")),
start_time_field(new Graph_lib::In_box(Graph_lib::Point(START_BUTTONS_POSITION_X+130, BUTTON_HEIGHT*2-MARGIN),
    BUTTON_WIDTH, BUTTON_HEIGHT-20, "Start (hours:minutes):")),
end_time_field(new Graph_lib::In_box(Graph_lib::Point(START_BUTTONS_POSITION_X+130, BUTTON_HEIGHT*3-MARGIN*2),
    BUTTON_WIDTH, BUTTON_HEIGHT-20, "End (hours:minutes):")),
end_day_field(new Graph_lib::In_box(Graph_lib::Point(START_BUTTONS_POSITION_X+130, BUTTON_HEIGHT*4-MARGIN*3),
    BUTTON_WIDTH, BUTTON_HEIGHT-20, "Day end: ")),
end_month_field(new Graph_lib::In_box(Graph_lib::Point(START_BUTTONS_POSITION_X+130, BUTTON_HEIGHT*5-MARGIN*4),
    BUTTON_WIDTH, BUTTON_HEIGHT-20, "Month end: ")),
end_year_field(new Graph_lib::In_box(Graph_lib::Point(START_BUTTONS_POSITION_X+130, BUTTON_HEIGHT*6-MARGIN*5),
    BUTTON_WIDTH, BUTTON_HEIGHT-20, "Year end: ")),
go_back(new MyButton({0, BASIC_WINDOW_HEIGHT-BUTTON_HEIGHT}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Back", button->task, GoBackCB)),
Note1(new Graph_lib::Text(Graph_lib::Point{MARGIN, BASIC_WINDOW_HEIGHT-MARGIN*5}, NOTE1)),
Note2(new Graph_lib::Text(Graph_lib::Point{MARGIN, BASIC_WINDOW_HEIGHT-MARGIN*4}, NOTE2))
{
    attach(*new_data_button);
    attach(*new_name_field);
    attach(*new_info_field);
    attach(*start_time_field);
    attach(*end_time_field);
    attach(*go_back);
    attach(*Note1);
    attach(*Note2);
    attach(*end_day_field);
    attach(*end_month_field);
    attach(*end_year_field);
}

void AddTaskWindow::SetTaskCB(Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<AddTaskWindow&>(btn.window()).SetTask();
}

void AddTaskWindow::SetTask() {
    std::string name = new_name_field->get_string();
    std::string info = new_info_field->get_string();
    std::string start = start_time_field->get_string();
    std::string end = end_time_field->get_string();
    std::string end_day = end_day_field->get_string();
    std::string end_month = end_month_field->get_string();
    std::string end_year = end_year_field->get_string();

    if (name.size() == 0) name = "default";
    if (info.size() == 0) info = "default";

    unsigned hours_start{INVALID_TIME}, minutes_start{INVALID_TIME};

    try {
        size_t colonPos = start.find(':');

        hours_start = std::stoi(start.substr(0, colonPos));
        minutes_start = std::stoi(start.substr(colonPos + 1));
        if (hours_start < 0 || hours_start >= 24 || minutes_start < 0 || minutes_start >= 60) {
            hours_start = 0;
            minutes_start = 0;
        }
    }
    catch (...) {
        hours_start = 0;
        minutes_start = 0;
    }
    unsigned hours_end{INVALID_TIME}, minutes_end{INVALID_TIME};
    try {
        size_t colonPos = end.find(':');

        hours_end = std::stoi(end.substr(0, colonPos));
        minutes_end = std::stoi(end.substr(colonPos + 1));
        if (hours_end < 0 || hours_end >= 24 || minutes_end < 0 || minutes_end >= 60) {
            hours_end = 0;
            minutes_end = 0;
        }
    }
    catch(...) {
        hours_end = 1;
        minutes_end = 1;
    }


    unsigned day_end{0};
    unsigned month_end{0};
    unsigned year_end{0};

    try {
        month_end = std::stoi(end_month);
        --month_end;
    }
    catch(...) {
        month_end = static_cast<int>(day_window->date.month());
    }
    try {
        year_end = std::stoi(end_year);
    }
    catch(...) {
        year_end = day_window->date.year();
    }
    try {
        day_end = std::stoi(end_day);
    }
    catch(...) {
        day_end = day_window->date.day();
    }

    TaskManager_ns::Task* task = new TaskManager_ns::Task(name, info,
        {hours_start, minutes_start,
            {static_cast<double>(day_window->date.day()),
                day_window->date.month(), static_cast<double>(day_window->date.year())},
            hours_end, minutes_end,
            {static_cast<double>(day_end), static_cast<Chrono_ns::Month>(month_end), static_cast<double>(year_end)}});
    day_window->addTask(task);
    day_window->redraw();
}

void AddTaskWindow::GoBackCB(Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<AddTaskWindow&>(btn.window()).goBack();
}

void AddTaskWindow::goBack() {
    std::cout << "went back" << std::endl;
    this->hide();
}