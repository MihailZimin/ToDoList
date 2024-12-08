//
// Created by Misha on 25.11.2024.
//

#ifndef TASKWINDOW_H
#define TASKWINDOW_H


#include "Graph_lib/Window.h"
#include "Graph_lib/GUI.h"
#include "MyButton.h"
#include "DayDraw.h"

class TaskWindow: public Graph_lib::Window{
public:
    TaskWindow(MyButton* button, DayWindow* day_window);

    static void ChangeTaskNameCB(Graph_lib::Address, Graph_lib::Address pw);
    static void GoBackCB(Graph_lib::Address, Graph_lib::Address pw);
    static void DeleteTaskCB(Graph_lib::Address, Graph_lib::Address pw);

    void ChangeTaskName(MyButton& btn);
    void goBack();
    void deleteTask();

    Graph_lib::Text* txt_info;
    Graph_lib::Text* txt_time;
    MyButton* changeTaskName;
    MyButton* go_back;
    MyButton* delete_task_button;
    DayWindow* day_window{nullptr};
    bool need_to_be_destroyed{true};
    MyButton* button;


    void hide() override {
        Window::hide();
        this->day_window->need_to_be_destroyed = true;
        if (need_to_be_destroyed) {
            this->day_window->show();
            delete this;
        }
    }

    ~TaskWindow() override {
        std::cout << "TaskWindow::~TaskWindow" << std::endl;
        // delete txt_info;
        // delete txt_time;
        // delete changeTaskName;
        // delete go_back;
        // delete delete_task_button;
        // delete button;
        day_window = nullptr;
    }
};


class AddTaskWindow: Graph_lib::Window {
public:
    AddTaskWindow(MyButton* button, DayWindow* day_window);

    Graph_lib::In_box* new_name_field;
    Graph_lib::In_box* new_info_field;
    Graph_lib::In_box* start_time_field;
    Graph_lib::In_box* end_time_field;
    MyButton* new_data_button;
    MyButton* go_back;
    DayWindow* day_window{nullptr};
    Graph_lib::Text* Note1;
    Graph_lib::Text* Note2;

    static void SetTaskCB(Graph_lib::Address, Graph_lib::Address pw);
    static void GoBackCB(Graph_lib::Address, Graph_lib::Address pw);

    void SetTask();
    void goBack();

    void hide() override {
        Window::hide();
        this->day_window->need_to_be_destroyed = true;
        this->day_window->show();
        delete this;
    }

    ~AddTaskWindow() override {
        std::cout << "AddTaskWindow::~AddTaskWindow" << std::endl;
        delete new_name_field;
        delete new_info_field;
        delete new_data_button;
        day_window = nullptr;
    }
};

#endif