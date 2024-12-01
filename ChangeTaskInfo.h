//
// Created by Misha on 25.11.2024.
//

#ifndef CHANGENAMEWINDOW_H
#define CHANGENAMEWINDOW_H
#include "Graph_lib/GUI.h"
#include "MyButton.h"

class ChangeTaskInfo: Graph_lib::Window{
public:
    ChangeTaskInfo(MyButton* button, TaskWindow* window);

    static void GetName(Graph_lib::Address, Graph_lib::Address pw);
    static void GetInfo(Graph_lib::Address, Graph_lib::Address pw);
    static void GetTime(Graph_lib::Address, Graph_lib::Address pw);

    Graph_lib::In_box* new_name_field;
    Graph_lib::In_box* new_info_field;
    Graph_lib::In_box* new_time_field;
    MyButton* new_data_button;
    MyButton* new_time_button;
    MyButton* new_info_button;
    TaskWindow* task_window{nullptr};

    void changeName(Task& task);
    void changeInfo(Task& task);
    void changeTime(Task& task);

    void hide() override {
        Window::hide();
        delete this;
    }


    ~ChangeTaskInfo() override{
        std::cout << "Destructor ChangeTaskInfo" << std::endl;
        delete new_name_field;
        delete new_info_field;
        delete new_info_button;
        delete new_data_button;
        delete new_time_button;
        task_window = nullptr;
    }
};

#endif //CHANGENAMEWINDOW_H
