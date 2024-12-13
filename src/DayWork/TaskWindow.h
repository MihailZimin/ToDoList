//
// Created by Misha on 25.11.2024.
//

#ifndef TASKWINDOW_H
#define TASKWINDOW_H


#include "../Graph_lib/Window.h"
#include "../Graph_lib/GUI.h"
#include "MyWidgets.h"
#include "DayDraw.h"


class TaskWindow: public Graph_lib::Window{
public:
    TaskWindow(MyButton& button_from_called, DayWindow* day_window);

    static void ChangeTaskDetailsCB(Graph_lib::Address, Graph_lib::Address pw);
    static void GoBackCB(Graph_lib::Address, Graph_lib::Address pw);
    static void DeleteTaskCB(Graph_lib::Address, Graph_lib::Address pw);

    void ChangeTaskDetails(MyButton& btn);
    void GoBack();
    void DeleteTask();

    Graph_lib::Text txt_info;
    Graph_lib::Text txt_time_start;
    Graph_lib::Text txt_time_end;
    MyButton change_task_details;
    MyButton go_back;
    MyButton delete_task_button;
    MyButton& button_from_called;
    DayWindow* day_window{nullptr};

};
#endif