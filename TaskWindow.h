//
// Created by Misha on 25.11.2024.
//

#ifndef TASKWINDOW_H
#define TASKWINDOW_H

#include "DayLogic.h"
#include "Graph_lib/Window.h"
#include "Graph_lib/GUI.h"
#include "MyButton.h"


class TaskWindow: Graph_lib::Window{
public:
    TaskWindow(MyButton* button, DayWindow* day_window);

    static void ChangeTaskName(Graph_lib::Address, Graph_lib::Address pw);

    Graph_lib::Text* txt_info{};
    Graph_lib::Text* txt_time{};
    MyButton* changeTaskName{};
    DayWindow* day_window{nullptr};

    void Redraw() {
        redraw();
    }

    void hide() override {
        Window::hide();
        delete this;
    }

    ~TaskWindow() override {
        std::cout << "TaskWindow::~TaskWindow" << std::endl;
        delete txt_info;
        delete txt_time;
        delete changeTaskName;
        day_window = nullptr;
    }

};


class AddTaskWindow: Graph_lib::Window {
public:
    AddTaskWindow(MyButton* button, DayWindow* day_window);

    Graph_lib::In_box* new_name_field;
    Graph_lib::In_box* new_info_field;
    MyButton* new_data_button;
    DayWindow* day_window{nullptr};

    static void SetTaskCB(Graph_lib::Address, Graph_lib::Address pw);

    void SetTask();

    void hide() override {
        Window::hide();
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


class RemoveTaskWindow: Graph_lib::Window {
public:
    RemoveTaskWindow(MyButton* button, DayWindow* day_window);

    Graph_lib::In_box* time_field;
    MyButton* delete_button;
    DayWindow* day_window{nullptr};

    static void DelTaskCB(Graph_lib::Address, Graph_lib::Address pw);

    void DelTask();


    void hide() override {
        Window::hide();
        delete this;
    }

    ~RemoveTaskWindow() override {
        std::cout << "RemoveTaskWindow::~RemoveTaskWindow" << std::endl;
        delete time_field;
        delete delete_button;
        day_window = nullptr;
    }
};


#endif //TASKWINDOW_H
