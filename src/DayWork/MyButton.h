
// Created by Misha on 25.11.2024.
//

#ifndef MYBUTTON_H
#define MYBUTTON_H

#include "../Graph_lib/GUI.h"
#include "toDoListFileWork/to_do_list/task_manager.h"


class ChangeTaskInfo;
class TaskWindow;
class DayWindow;
class AddTaskWindow;

class MyButton : public Graph_lib::Button {
public:

    MyButton(Graph_lib::Point xy, int w, int h, const std::string& label, Graph_lib::Callback cb):
        x_coord(xy.x), y_coord(xy.y),
        Button{xy, w, h, label, cb}{}
    MyButton(Graph_lib::Point xy, int w, int h, const std::string& label, Graph_lib::Callback cb, Fl_Color color):
        x_coord(xy.x), y_coord(xy.y), color(color),
        Button{xy, w, h, label, cb}{}
    MyButton(Graph_lib::Point xy, int w, int h, const std::string& label, TaskManager_ns::Task* task,
        Graph_lib::Callback cb) :
        x_coord(xy.x), y_coord(xy.y),
        Button{xy, w, h, label, cb}, task(task){}
    MyButton(Graph_lib::Point xy, int w, int h, const std::string& label, TaskManager_ns::Task* task,
        Graph_lib::Callback cb, Fl_Color color) :
        x_coord(xy.x), y_coord(xy.y), color(color),
        Button{xy, w, h, label, cb}, task(task){}

    void set_font (Graph_lib::Font f) { fnt = f; }

    int x_coord{0};
    int y_coord{0};
    TaskManager_ns::Task* task;

    ~MyButton() override {
        delete task;
    }

    void attach(Graph_lib::Window &) override;

private:
    Graph_lib::Font fnt{fl_font()};
    Fl_Color color{fl_rgb_color(192, 192, 192)};
};

#endif //MYBUTTON_H