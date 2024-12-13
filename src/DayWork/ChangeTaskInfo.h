//
// Created by Misha on 25.11.2024.
//

#ifndef CHANGENAMEWINDOW_H
#define CHANGENAMEWINDOW_H

#include "../Graph_lib/GUI.h"
#include "MyWidgets.h"
#include "TaskWindow.h"

struct Information {
    std::string name;
    std::string text;
    std::string start;
    std::string end;
    std::string end_day;
    std::string end_month;
    std::string end_year;
};


bool is_end_date_greater(int day_start, int month_start, int year_start,
        int day_end, int month_end, int year_end);


class WindowTaskChanger: public Graph_lib::Window {
public:

    explicit WindowTaskChanger(const MyButton& button_from_called);
    explicit WindowTaskChanger();

    static void changeTaskCB(Graph_lib::Address, Graph_lib::Address pw);
    static void goBackCB(Graph_lib::Address, Graph_lib::Address pw);
    static void openHelpWindowCB(Graph_lib::Address, Graph_lib::Address pw);

    virtual void changeTask(TaskManager_ns::Task& task) {}
    virtual void setTask() {}
    virtual void goBack() {}
    virtual void openHelpWindow() {}
    virtual void setColor(Fl_Color color);
    virtual void setPeriodColor(Fl_Color color);
    virtual Information processData();
    virtual void checkDefaultStates(Information& info);
    virtual void reattachFields(const Information& info);

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

};


class ChangeTaskInfo: public WindowTaskChanger{
public:
    ChangeTaskInfo(MyButton& button_from_called, TaskWindow* window);

    void changeTask(TaskManager_ns::Task& task) override;
    void goBack() override;
    void openHelpWindow() override;


    MyButton& button_from_called;
    TaskWindow* task_window{nullptr};
};


class AddTaskWindow: public WindowTaskChanger {
public:
    explicit AddTaskWindow(DayWindow* day_window);

    void setTask() override;
    void goBack() override;
    void openHelpWindow() override;

    DayWindow* day_window{nullptr};
};


#endif //CHANGENAMEWINDOW_H