//
// Created by Misha on 25.11.2024.
//

#include "TaskWindow.h"

#include "ChangeTaskInfo.h"
#include "PARAMETERS.h"
#include "DayDraw.h"


void TaskWindow::ChangeTaskName(Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    ChangeTaskInfo* changeNameWin = new ChangeTaskInfo(&btn, &reinterpret_cast<TaskWindow&>(btn.window()));
}


TaskWindow::TaskWindow(MyButton* button, DayWindow* day_window):
        day_window(day_window),
        Graph_lib::Window(Graph_lib::Point(100, 100), 400, 300, "Task"),
        txt_info(new Graph_lib::Text(START_TEXT_POSITION, "Info: "+ button->task->details)),
        txt_time(new Graph_lib::Text(START_TEXT_TIME_POSITION, "Time: "+ button->task->name)),
        changeTaskName(new MyButton({10, 10}, 80, 30, "Change info",
                button->task, ChangeTaskName))
{
    attach(*changeTaskName);
    attach(*txt_info);
    attach(*txt_time);
}



AddTaskWindow::AddTaskWindow(MyButton *button, DayWindow *day_window):
        Graph_lib::Window(Graph_lib::Point(100, 100), 400, 300, "Add Task Window"),
        day_window{day_window},
        new_name_field(new Graph_lib::In_box(Graph_lib::Point(START_BUTTONS_POSITION_X+130, 10),
            80, 30, "Enter task name:")),
        new_data_button(new MyButton({START_BUTTONS_POSITION_X+220, 10}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
            "Set task", button->task,
                SetTaskCB)),
        new_info_field(new Graph_lib::In_box(Graph_lib::Point(START_BUTTONS_POSITION_X+130, START_BUTTONS_POSITION_Y+10),
            80, 30, "Enter information about task:"))
{
    attach(*new_data_button);
    attach(*new_name_field);
    attach(*new_info_field);
}

void AddTaskWindow::SetTaskCB(Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<AddTaskWindow&>(btn.window()).SetTask();
}

void AddTaskWindow::SetTask() {
    std::string name = new_name_field->get_string();
    std::string info = new_info_field->get_string();
    Task* task = new Task(name, info);
    day_window->addTask(task);
    day_window->Redraw();
}


RemoveTaskWindow::RemoveTaskWindow(MyButton *button, DayWindow *day_window):
        day_window(day_window),
        Graph_lib::Window(Graph_lib::Point(100, 100), 400, 300, "Add Task Window"),
        time_field(new Graph_lib::In_box(Graph_lib::Point(START_BUTTONS_POSITION_X+200, 10),
            80, 30, "Enter time of task you want to remove:")),
        delete_button(new MyButton({START_BUTTONS_POSITION_X+300, 10}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Delete", button->task,
        DelTaskCB))
{
    attach(*time_field);
    attach(*delete_button);

}

void RemoveTaskWindow::DelTaskCB(Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<RemoveTaskWindow&>(btn.window()).DelTask();
}

void RemoveTaskWindow::DelTask() {
    std::string name = time_field->get_string();
    day_window->removeTask(name);
    day_window->Redraw();
}

