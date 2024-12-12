//
// Created by Misha on 11.12.2024.
//

#include "PARAMETERS.h"
#include "TaskWindow.h"
#include "HelpWindow.h"
#include "ChangeTaskInfo.h"


void HelpWindow::goBackCB(Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<HelpWindow&>(btn.window()).goBack();
}

void HelpWindow::goBack(){}


HelpWindow::HelpWindow():
    Window(BASIC_WINDOW_POSITION, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT, ""),
go_back(MyButton({0, BASIC_WINDOW_HEIGHT-BUTTON_HEIGHT}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Back", goBackCB)),
Note0(Graph_lib::Text(Graph_lib::Point{MARGIN, MARGIN}, NOTE0)),
Note1(Graph_lib::Text(Graph_lib::Point{MARGIN, MARGIN+NOTES_SIZE}, NOTE1)),
Note2(Graph_lib::Text(Graph_lib::Point{MARGIN, MARGIN+NOTES_SIZE*2}, NOTE2)),
Note3(Graph_lib::Text(Graph_lib::Point{MARGIN, MARGIN+NOTES_SIZE*3}, NOTE3)),
Note4(Graph_lib::Text(Graph_lib::Point{MARGIN, MARGIN+NOTES_SIZE*4}, NOTE4)),
Note5(Graph_lib::Text(Graph_lib::Point{MARGIN, MARGIN+NOTES_SIZE*5}, NOTE5)),
Note6(Graph_lib::Text(Graph_lib::Point{MARGIN, MARGIN+NOTES_SIZE*6}, NOTE6)),
Note7(Graph_lib::Text(Graph_lib::Point{MARGIN, MARGIN+NOTES_SIZE*7}, NOTE7))
{
    size_range(BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT);

    attach(go_back);
    attach(Note0);
    attach(Note1);
    attach(Note2);
    attach(Note3);
    attach(Note4);
    attach(Note5);
    attach(Note6);
    attach(Note7);
}

void HelpAddTaskWindow::goBack() {
    this->hide();
    add_task_window->show();
}

HelpAddTaskWindow::HelpAddTaskWindow(AddTaskWindow *add_task_window)
{
    this->add_task_window = add_task_window;
}

void HelpChangeTaskWindow::goBack() {
    this->hide();
    change_task_info->show();
}

HelpChangeTaskWindow::HelpChangeTaskWindow(ChangeTaskInfo *change_task_info) {
    this->change_task_info = change_task_info;
}
