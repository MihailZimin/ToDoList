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


TaskWindow::TaskWindow(MyButton* button, DayWindow* day_window) :
day_window(day_window),
Graph_lib::Window(BASIC_WINDOW_POSITION, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT, "Task"),
txt_info(new Graph_lib::Text(START_TEXT_POSITION, "Info: "+ button->task->text)),
txt_time(new Graph_lib::Text(START_TEXT_TIME_POSITION, "Time: "+ button->task->name)),
changeTaskName(new MyButton({10, 10}, 80, 30, "Change info",
        button->task, ChangeTaskNameCB)),
go_back(new MyButton({0, BASIC_WINDOW_HEIGHT-BUTTON_HEIGHT}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Back", button->task, GoBackCB))
{
    attach(*changeTaskName);
    attach(*txt_info);
    attach(*txt_time);
    attach(*go_back);
}



AddTaskWindow::AddTaskWindow(MyButton *button, DayWindow *day_window):
Graph_lib::Window(BASIC_WINDOW_POSITION, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT, "Add Task Window"),
day_window{day_window},
new_name_field(new Graph_lib::In_box(Graph_lib::Point(START_BUTTONS_POSITION_X+130, 10),
    80, 30, "Enter task name:")),
new_data_button(new MyButton({START_BUTTONS_POSITION_X+220, 10}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Set task", button->task,
        SetTaskCB)),
new_info_field(new Graph_lib::In_box(Graph_lib::Point(START_BUTTONS_POSITION_X+130, START_BUTTONS_POSITION_Y+10),
    80, 30, "Enter information about task:")),
go_back(new MyButton({0, BASIC_WINDOW_HEIGHT-BUTTON_HEIGHT}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Back", button->task, GoBackCB))
{
    attach(*new_data_button);
    attach(*new_name_field);
    attach(*new_info_field);
    attach(*go_back);
}

void AddTaskWindow::SetTaskCB(Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<AddTaskWindow&>(btn.window()).SetTask();
}

void AddTaskWindow::SetTask() {
    std::string name = new_name_field->get_string();
    std::string info = new_info_field->get_string();
    TaskManager_ns::Task* task = new TaskManager_ns::Task(name, info,
        {1, 2, {1, Chrono_ns::Month::apr, 1},
            1, 2, {1, Chrono_ns::Month::jul, 1}});
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

RemoveTaskWindow::RemoveTaskWindow(MyButton *button, DayWindow *day_window):
day_window(day_window),
Graph_lib::Window(BASIC_WINDOW_POSITION, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT, "Add Task Window"),
time_field(new Graph_lib::In_box(Graph_lib::Point(START_BUTTONS_POSITION_X+200, 10),
    80, 30, "Enter time of task you want to remove:")),
delete_button(new MyButton({START_BUTTONS_POSITION_X+300, 10}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
"Delete", button->task,
        DelTaskCB)),
go_back(new MyButton({0, BASIC_WINDOW_HEIGHT-BUTTON_HEIGHT}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Back", button->task, GoBackCB))
{
    attach(*time_field);
    attach(*delete_button);
    attach(*go_back);

}

void RemoveTaskWindow::DelTaskCB(Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<RemoveTaskWindow&>(btn.window()).DelTask();
}

void RemoveTaskWindow::DelTask() {
    std::string name = time_field->get_string();
    day_window->removeTask(name);
    day_window->redraw();
}

void RemoveTaskWindow::GoBackCB(Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<RemoveTaskWindow&>(btn.window()).goBack();
}

void RemoveTaskWindow::goBack() {
    std::cout << "went back" << std::endl;
    this->hide();
}