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
change_task_details(MyButton({10, 10}, 80, 30, "Change info",
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

    attach(change_task_details);
    attach(txt_info);
    attach(txt_time_start);
    attach(txt_time_end);
    attach(go_back);
    attach(delete_task_button);
}