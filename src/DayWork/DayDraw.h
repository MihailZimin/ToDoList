#ifndef DAYDRAW_H
#define DAYDRAW_H


#include <toDoListFileWork/to_do_list/task_manager.h>
#include "Graph_lib/Window.h"
#include "Graph_lib/GUI.h"
#include "Graph_lib/Graph.h"
#include "MyWidgets.h"
#include "PARAMETERS.h"
#include "MainWindowPart/date_button.h"

class WeekWindow;
class Month;


class DayWindow: public Graph_lib::Window {
public:
    DayWindow(Graph_lib::Point pos, int width, int height, Chrono_ns::Date& date, const std::string& day, DateButton* datebutton);

    void removeTask();
    void updateTasks();
    void redrawButtons();
    void removeTask(TaskManager_ns::Task& task);
    void addTask(TaskManager_ns::Task* task);

    static void addTaskWindowCB(Graph_lib::Address, Graph_lib::Address pw);
    static void showTaskInfoCB(Graph_lib::Address, Graph_lib::Address pw);
    static void removeTaskCB(Graph_lib::Address, Graph_lib::Address pw);
    static void closeWindowCB(Graph_lib::Address, Graph_lib::Address pw);
    static void nextWindowCB(Graph_lib::Address, Graph_lib::Address pw);
    static void prevWindowCB(Graph_lib::Address, Graph_lib::Address pw);

    void showTaskInfoWindow(MyButton& btn);
    void addTaskWindow();
    void closeWindow();
    void nextWindow();
    void prevWindow();


    MyButton add_task_button;
    MyButton close_window_button;
    MyButton next_button;
    MyButton prev_button;

    Graph_lib::Text information;
    Graph_lib::Text dayName;

    MyButton* CreateButton(TaskManager_ns::Task* task);

    Chrono_ns::Date date;

    WeekWindow* week_window;
    Month* month_window;

    DateButton* day_from_called;

    bool from_month{false};

    Graph_lib::Vector_ref<MyButton> buttons;

    const std::string day;


private:
    int pos_x = START_BUTTONS_POSITION_X;
    int pos_y = START_BUTTONS_POSITION_Y;
    int font_size{20};
    std::vector<TaskManager_ns::Task> tasks;
    int current_buttons_window = 0;
};

#endif //DAYDRAW_H