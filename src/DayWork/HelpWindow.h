//
// Created by Misha on 11.12.2024.
//

#ifndef NOTEWINDOW_H
#define NOTEWINDOW_H
#include <Graph_lib/GUI.h>
#include <Graph_lib/Window.h>

#include "MyWidgets.h"


class HelpWindow: public Graph_lib::Window {
public:
    HelpWindow();

    static void goBackCB(Graph_lib::Address, Graph_lib::Address pw);

    virtual void goBack();

    MyButton go_back;

    ChangeTaskInfo* change_task_info{nullptr};
    AddTaskWindow* add_task_window{nullptr};

    Graph_lib::Text Note0;
    Graph_lib::Text Note1;
    Graph_lib::Text Note2;
    Graph_lib::Text Note3;
    Graph_lib::Text Note4;
    Graph_lib::Text Note5;
    Graph_lib::Text Note6;
    Graph_lib::Text Note7;

};

class HelpAddTaskWindow: public HelpWindow{
public:
    explicit HelpAddTaskWindow(AddTaskWindow* add_task_window);

    void goBack() override;

};

class HelpChangeTaskWindow: public HelpWindow{
public:
    explicit HelpChangeTaskWindow(ChangeTaskInfo* add_task_window);

    void goBack() override;

};

#endif //NOTEWINDOW_H