
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
    MyButton(Graph_lib::Point xy, int w, int h, const std::string& label, TaskManager_ns::Task* task,
        Graph_lib::Callback cb) :
        x_coord(xy.x), y_coord(xy.y),
        Button{xy, w, h, label, cb}, task(task){}

    int x_coord{0};
    int y_coord{0};
    TaskManager_ns::Task* task;

    ~MyButton() override {
        delete task;
    }
};

#endif //MYBUTTON_H