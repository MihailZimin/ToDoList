//
// Created by Misha on 25.11.2024.
//

#ifndef CHANGENAMEWINDOW_H
#define CHANGENAMEWINDOW_H
#include "../Graph_lib/GUI.h"
#include "MyButton.h"
#include "TaskWindow.h"


class ChangeTaskInfo: public Graph_lib::Window{
public:
    ChangeTaskInfo(MyButton* button, TaskWindow* window);

    static void changeTaskCB(Graph_lib::Address, Graph_lib::Address pw);
    static void GoBackCB(Graph_lib::Address, Graph_lib::Address pw);

    Graph_lib::In_box* new_name_field;
    Graph_lib::In_box* new_text_field;
    Graph_lib::In_box* new_start_time_field;
    Graph_lib::In_box* new_end_time_field;
    Graph_lib::In_box* new_end_day_field;
    Graph_lib::In_box* new_end_month_field;
    Graph_lib::In_box* new_end_year_field;
    MyButton* new_info_button;
    MyButton* go_back;
    MyButton* note_button;
    TaskWindow* task_window{nullptr};
    Graph_lib::Text* Note0_0;

    void changeTask(TaskManager_ns::Task& task);
    void goBack();

    void hide() override{
        Window::hide();
        this->task_window->day_window->show();
        this->task_window->need_to_be_destroyed = true;
        delete this;
    }

    ~ChangeTaskInfo() override;

};

#endif //CHANGENAMEWINDOW_H
