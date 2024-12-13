//
// Created by Misha on 21.11.2024.
//

#ifndef DAYDRAW_H
#define DAYDRAW_H


#include <toDoListFileWork/to_do_list/task_manager.h>
#include "Graph_lib/Window.h"
#include "Graph_lib/GUI.h"
#include "Graph_lib/Graph.h"
#include "MyWidgets.h"

class DayWindow: public Graph_lib::Window {
public:
    DayWindow(int width, int height, Chrono_ns::Date& date, const std::string& day);

    void removeTask();
    void updateTasks();
    void redrawButtons();
    void removeTask(TaskManager_ns::Task& task);
    void addTask(TaskManager_ns::Task* task);
    TaskManager_ns::TaskManager task_manager;

    static void addTaskWindowCB(Graph_lib::Address, Graph_lib::Address pw);
    static void showTaskInfoCB(Graph_lib::Address, Graph_lib::Address pw);
    static void removeTaskCB(Graph_lib::Address, Graph_lib::Address pw);
    static void closeWindowCB(Graph_lib::Address, Graph_lib::Address pw);
    static void openNotesCB(Graph_lib::Address, Graph_lib::Address pw);

    void showTaskInfoWindow(MyButton& btn);
    void addTaskWindow();
    void openNotes();


    MyButton add_task_button;
    MyButton close_window_button;

    Graph_lib::Text information;
    Graph_lib::Text dayName;

    MyButton* CreateButton(TaskManager_ns::Task* task);

    Chrono_ns::Date date;

private:
    int pos_x = 50;
    int pos_y = 10;
    int font_size{20};
    std::vector<TaskManager_ns::Task> tasks;
    Graph_lib::Vector_ref<MyButton> buttons;
    const std::string day;
};

#endif //DAYDRAW_H