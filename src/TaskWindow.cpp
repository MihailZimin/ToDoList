//
// Created by Misha on 25.11.2024.
//

#include "TaskWindow.h"

#include "ChangeTaskInfo.h"
#include "PARAMETERS.h"
#include "DayDraw.h"


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
txt_info(new Graph_lib::Text(START_TEXT_POSITION, "Info: "+ button->task->text)),
txt_time(new Graph_lib::Text(START_TEXT_TIME_POSITION, "Time: "+ button->task->name)),
changeTaskName(new MyButton({10, 10}, 80, 30, "Change info",
        button->task, ChangeTaskNameCB)),
go_back(new MyButton({0, BASIC_WINDOW_HEIGHT-BUTTON_HEIGHT}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Back", button->task, GoBackCB)),
delete_task_button(new MyButton({BASIC_WINDOW_WIDTH-BUTTON_WIDTH-30, 0}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Delete", button->task, DeleteTaskCB))
{
    //std::cout << "id: " << button->task->get_id() << '\n';
    std::cout << "something" << '\n';
    attach(*changeTaskName);
    attach(*txt_info);
    attach(*txt_time);
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
    BUTTON_WIDTH, BUTTON_HEIGHT-20, "Enter information about task:")),
start_time_field(new Graph_lib::In_box(Graph_lib::Point(START_BUTTONS_POSITION_X+130, BUTTON_HEIGHT*2-MARGIN),
    BUTTON_WIDTH, BUTTON_HEIGHT-20, "Start (hours:minutes):")),
end_time_field(new Graph_lib::In_box(Graph_lib::Point(START_BUTTONS_POSITION_X+130, BUTTON_HEIGHT*3-MARGIN*2),
    BUTTON_WIDTH, BUTTON_HEIGHT-20, "End (hours:minutes):")),
go_back(new MyButton({0, BASIC_WINDOW_HEIGHT-BUTTON_HEIGHT}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Back", button->task, GoBackCB)),
Note1(new Graph_lib::Text(Graph_lib::Point{0, BASIC_WINDOW_HEIGHT-MARGIN*5}, NOTE1)),
Note2(new Graph_lib::Text(Graph_lib::Point{0, BASIC_WINDOW_HEIGHT-MARGIN*4}, NOTE2))
{
    attach(*new_data_button);
    attach(*new_name_field);
    attach(*new_info_field);
    attach(*start_time_field);
    attach(*end_time_field);
    attach(*go_back);
    attach(*Note1);
    attach(*Note2);
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

    if (name.size() == 0) name = "default";
    if (info.size() == 0) info = "default";

    unsigned hours_start{INVALID_TIME}, minutes_start{INVALID_TIME};

    try {
        size_t colonPos = start.find(':');

        hours_start = std::stoi(start.substr(0, colonPos));
        minutes_start = std::stoi(start.substr(colonPos + 1));
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
    }
    catch(...) {
        hours_end = 0;
        minutes_end = 0;
    }

    TaskManager_ns::Task* task = new TaskManager_ns::Task(name, info,
        {hours_start, minutes_start, {1, Chrono_ns::Month::apr, 1},
            hours_end, minutes_end, {1, Chrono_ns::Month::jul, 1}});
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