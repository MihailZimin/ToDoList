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
    MyButton changeTaskName;
    MyButton go_back;
    MyButton delete_task_button;
    MyButton& button_from_called;
    DayWindow* day_window{nullptr};

    virtual void show() override {
        Window::show();
    }


    ~TaskWindow() override {
        day_window = nullptr;
    }
};


class AddTaskWindow: public Graph_lib::Window {
public:
    explicit AddTaskWindow(DayWindow* day_window);

    static void setTaskCB(Graph_lib::Address, Graph_lib::Address pw);
    static void goBackCB(Graph_lib::Address, Graph_lib::Address pw);
    static void openHelpWindowCB(Graph_lib::Address, Graph_lib::Address pw);

    void setTask();
    void goBack();
    void openHelpWindow();

    Graph_lib::In_box new_name_field;
    Graph_lib::In_box new_info_field;
    Graph_lib::In_box start_time_field;
    Graph_lib::In_box end_time_field;
    Graph_lib::In_box end_day_field;
    Graph_lib::In_box end_month_field;
    Graph_lib::In_box end_year_field;
    MyButton new_data_button;
    MyButton go_back;
    MyButton show_help;
    DayWindow* day_window{nullptr};


    ~AddTaskWindow() override {
        day_window = nullptr;
    }
};

#endif