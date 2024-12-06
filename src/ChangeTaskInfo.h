//
// Created by Misha on 25.11.2024.
//

#ifndef CHANGENAMEWINDOW_H
#define CHANGENAMEWINDOW_H
#include "Graph_lib/GUI.h"
#include "MyButton.h"
#include "TaskWindow.h"


class ChangeTaskInfo: public Graph_lib::Window{
public:
    ChangeTaskInfo(MyButton* button, TaskWindow* window);

    static void GetName(Graph_lib::Address, Graph_lib::Address pw);
    static void GetInfo(Graph_lib::Address, Graph_lib::Address pw);
    static void GetTime(Graph_lib::Address, Graph_lib::Address pw);
    static void GoBackCB(Graph_lib::Address, Graph_lib::Address pw);

    Graph_lib::In_box* new_name_field;
    Graph_lib::In_box* new_info_field;
    Graph_lib::In_box* new_time_field;
    MyButton* new_data_button;
    MyButton* new_time_button;
    MyButton* new_info_button;
    MyButton* go_back;
    TaskWindow* task_window{nullptr};

    void changeName(TaskManager_ns::Task& task);
    void changeInfo(TaskManager_ns::Task& task);
    void changeTime(TaskManager_ns::Task& task);
    void goBack();

    void hide() override;


    ~ChangeTaskInfo() override;

};

#endif //CHANGENAMEWINDOW_H
