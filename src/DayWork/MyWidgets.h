
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

    ~MyButton() override {
        delete task;
    }

    void attach(Graph_lib::Window &) override;

    int x_coord{0};
    int y_coord{0};
    TaskManager_ns::Task* task;


    Graph_lib::Font fnt{fl_font()};
    Fl_Color color{fl_rgb_color(192, 192, 192)};
};

class MyIn_box: public Graph_lib::In_box {
public:
    MyIn_box(Graph_lib::Point xy, int w, int h, const std::string& s)
        : In_box(xy, w, h, s) {}
    MyIn_box(Graph_lib::Point xy, int w, int h, const std::string& s, Fl_Color color)
        : In_box(xy, w, h, s), col(color) {}

    void attach(Graph_lib::Window &) override;

    void color(Fl_Color color){ col = color; }

    void set_inside_text(const std::string& str){ inside_text = str; }


private:
    Fl_Color col{fl_rgb_color(192, 192, 192)};
    std::string inside_text;

};

#endif //MYBUTTON_H