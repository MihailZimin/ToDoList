//
// Created by Misha on 25.11.2024.
//

#ifndef CHANGENAMEWINDOW_H
#define CHANGENAMEWINDOW_H

#include "../Graph_lib/GUI.h"
#include "MyButton.h"
#include "TaskWindow.h"


bool is_end_date_greater(int day_start, int month_start, int year_start,
        int day_end, int month_end, int year_end);

class ChangeTaskInfo: public Graph_lib::Window{
public:
    ChangeTaskInfo(MyButton& button_from_called, TaskWindow* window);

    static void changeTaskCB(Graph_lib::Address, Graph_lib::Address pw);
    static void goBackCB(Graph_lib::Address, Graph_lib::Address pw);
    static void openHelpWindowCB(Graph_lib::Address, Graph_lib::Address pw);

    void changeTask(TaskManager_ns::Task& task);
    void goBack();
    void openHelpWindow();

    Graph_lib::In_box new_name_field;
    Graph_lib::In_box new_text_field;
    Graph_lib::In_box new_start_time_field;
    Graph_lib::In_box new_end_time_field;
    Graph_lib::In_box new_end_day_field;
    Graph_lib::In_box new_end_month_field;
    Graph_lib::In_box new_end_year_field;

    MyButton new_info_button;
    MyButton go_back;
    MyButton show_help;
    MyButton& button_from_called;

    TaskWindow* task_window{nullptr};


    ~ChangeTaskInfo() override {
        task_window = nullptr;
    }

};

#endif //CHANGENAMEWINDOW_H