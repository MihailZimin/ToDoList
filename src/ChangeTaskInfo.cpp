//
// Created by Misha on 25.11.2024.
//

#include "ChangeTaskInfo.h"

#include <DayDraw.h>

#include "PARAMETERS.h"
#include "TaskWindow.h"



void ChangeTaskInfo::GetName (Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<ChangeTaskInfo&>(btn.window()).changeName(*btn.task);
}

void ChangeTaskInfo::GetInfo (Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<ChangeTaskInfo&>(btn.window()).changeInfo(*btn.task);
}

void ChangeTaskInfo::GetTime(Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<ChangeTaskInfo&>(btn.window()).changeTime(*btn.task);
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
task_window(taskWindow),
new_name_field(new Graph_lib::In_box(Graph_lib::Point(START_BUTTONS_POSITION_X+130, 10),
    80, 30, "Enter new name:")),
new_data_button(new MyButton({START_BUTTONS_POSITION_X+220, 10}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Rename task", button->task, GetName)),
new_info_field(new Graph_lib::In_box(Graph_lib::Point(START_BUTTONS_POSITION_X+130, START_BUTTONS_POSITION_Y+10),
    80, 30, "Enter new information:")),
new_info_button(new MyButton({START_BUTTONS_POSITION_X+220, START_BUTTONS_POSITION_Y+10}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Change info", button->task,
        GetInfo)),
new_time_field(new Graph_lib::In_box(Graph_lib::Point(START_BUTTONS_POSITION_X+130, 2*START_BUTTONS_POSITION_Y+10),
    80, 30, "Enter new time:")),
new_time_button(new MyButton({START_BUTTONS_POSITION_X+220, 2*START_BUTTONS_POSITION_Y+10}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Change time", button->task, GetTime)),
go_back(new MyButton({0, BASIC_WINDOW_HEIGHT-BUTTON_HEIGHT}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Back", button->task, GoBackCB)),
Graph_lib::Window(BASIC_WINDOW_POSITION, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT, "Change Window")
{
    attach(*new_name_field);
    attach(*new_data_button);
    attach(*new_info_field);
    attach(*new_info_button);
    attach(*new_time_field);
    attach(*new_time_button);
    attach(*go_back);
}

void ChangeTaskInfo::changeName(Task& task) {
    std::string name = new_name_field->get_string();
    task.name = name;
    task_window->day_window->SetLabel(&task);
    task_window->day_window->redraw();
}

void ChangeTaskInfo::changeInfo(Task& task) {
    std::string info = new_info_field->get_string();
    task.details = info;
    task_window->txt_info->set_label("info:" + task.details);
    task_window->redraw();
}


void ChangeTaskInfo::changeTime(Task &task) {
    std::string time = new_time_field->get_string();
}


ChangeTaskInfo::~ChangeTaskInfo() {
    std::cout << "Destructor ChangeTaskInfo" << std::endl;
    delete new_name_field;
    delete new_info_field;
    delete new_info_button;
    delete new_data_button;
    delete new_time_button;
    task_window = nullptr;
}

void ChangeTaskInfo::hide() {
    Window::hide();
    this->task_window->show();
    this->task_window->need_to_be_destroyed = true;
    delete this;
}