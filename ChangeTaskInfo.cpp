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
        Graph_lib::Window(Graph_lib::Point(100, 100), 600, 400, "Change Window")
{
    attach(*new_name_field);
    attach(*new_data_button);
    attach(*new_info_field);
    attach(*new_info_button);
    attach(*new_time_field);
    attach(*new_time_button);
}

void ChangeTaskInfo::changeName(Task& task) {
    std::string name = new_name_field->get_string();
    task.name = name;
    task_window->day_window->SetLabel(&task);
    task_window->day_window->Redraw();
}

void ChangeTaskInfo::changeInfo(Task& task) {
    std::string info = new_info_field->get_string();
    task.details = info;
    task_window->txt_info->set_label(task.details);
    task_window->Redraw();
}


void ChangeTaskInfo::changeTime(Task &task) {
    std::string time = new_time_field->get_string();
}
