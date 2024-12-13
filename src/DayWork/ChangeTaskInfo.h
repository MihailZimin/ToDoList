//
// Created by Misha on 25.11.2024.
//

#ifndef CHANGENAMEWINDOW_H
#define CHANGENAMEWINDOW_H

#include "../Graph_lib/GUI.h"
#include "MyWidgets.h"
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
    void setColor(Fl_Color color);
    void setPeriodColor(Fl_Color color);
    void reattachFields(const std::string &name, const std::string &text, const std::string &start_time,
                    const std::string &end_time, const std::string &end_day, const std::string &end_month,
                    const std::string &end_year);

    MyIn_box new_name_field;
    MyIn_box new_text_field;
    MyIn_box new_start_time_field;
    MyIn_box new_end_time_field;
    MyIn_box new_end_day_field;
    MyIn_box new_end_month_field;
    MyIn_box new_end_year_field;

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