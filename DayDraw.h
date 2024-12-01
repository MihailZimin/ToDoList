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
#include "PARAMETERS.h"


class DayWindow: public Graph_lib::Window {
public:
    DayWindow(Day& day, int width, int height);

    void removeTask();

    void updateTasks();

    static void showTaskInfoCB(Graph_lib::Address, Graph_lib::Address pw);
    void showTaskInfo(MyButton& btn);

    static void addTaskCB(Graph_lib::Address, Graph_lib::Address pw);

    static void removeTaskCB(Graph_lib::Address, Graph_lib::Address pw);

    void Redraw() {
        redraw();
    }

    void RedrawButtons();

    void SetLabel(Task* task);

    void addTask(Task* task);

    void removeTask(std::string& task);

    MyButton* add_task_button;
    MyButton* remove_task_button;

    MyButton* CreateButton(Task& task);

    void resize(int X, int Y, int W, int H) override {
        Window::resize(X, Y, W, H);
        // dayName.move(-cur_width/2, 0);
        // dayName.move(W/2-10, 0);
        // cur_width = W;
        // cur_height = H;
        // double scale_factor = static_cast<double>(cur_width) / orig_width;
        // int new_size = static_cast<int>(font_size * scale_factor);
        // dayName.set_font_size(new_size);
    }

    ~DayWindow() override{
        delete add_task_button;
        delete remove_task_button;
    }

private:
    int pos_x = 50;
    int pos_y = 10;
    int cur_width{0};
    int cur_height{0};
    int orig_width{0};
    int orig_height{0};
    int font_size{20};
    Day& tasks;
    Graph_lib::Vector_ref<MyButton> buttons;
    Graph_lib::Text dayName;
};

#endif //DAYWINDOW_H
