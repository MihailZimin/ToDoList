//
// Created by Misha on 21.11.2024.
//

#ifndef DAYDRAW_H
#define DAYDRAW_H

#include "DayLogic.h"
#include "Graph_lib/Window.h"
#include "Graph_lib/GUI.h"
#include "Graph_lib/Graph.h"
#include "MyButton.h"


class DayWindow: public Graph_lib::Window {
public:
    DayWindow(Day& day, int width, int height);

    void removeTask();
    void updateTasks();
    void RedrawButtons();
    void SetLabel(Task* task);
    void removeTask(std::string& task);
    void addTask(Task* task);

    static void addTaskCB(Graph_lib::Address, Graph_lib::Address pw);
    static void showTaskInfoCB(Graph_lib::Address, Graph_lib::Address pw);
    static void removeTaskCB(Graph_lib::Address, Graph_lib::Address pw);

    void showTaskInfoWindow(MyButton& btn);
    void addTaskWindow(MyButton& btn);
    void removeTaskWindow(MyButton& btn);


    MyButton* add_task_button;
    MyButton* remove_task_button;
    bool need_to_be_destroyed{true};

    MyButton* CreateButton(Task& task);

    void hide() override {
        Window::hide();
        if (need_to_be_destroyed) delete this;
    }

    ~DayWindow() override{
        std::cout << "DayWindow::~DayWindow" << std::endl;
        delete add_task_button;
        delete remove_task_button;
    }

private:
    int pos_x = 50;
    int pos_y = 10;
    int font_size{20};
    Day& tasks;
    Graph_lib::Vector_ref<MyButton> buttons;
    Graph_lib::Text dayName;
};

#endif //DAYWINDOW_H
