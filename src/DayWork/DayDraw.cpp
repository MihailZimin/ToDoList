//
// Created by Misha on 21.11.2024.
//

#include "DayDraw.h"

#include "TaskWindow.h"
#include "PARAMETERS.h"

std::vector<TaskManager_ns::Task> tasks;

void DayWindow::showTaskInfoCB(Graph_lib::Address, Graph_lib::Address pw) {
    MyButton& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<DayWindow&>(btn.window()).showTaskInfoWindow(btn);
}

void DayWindow::showTaskInfoWindow(MyButton& btn) {
    TaskWindow* task_window = new TaskWindow(btn, this);
    this->hide();
}

void DayWindow::addTaskWindowCB(Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<DayWindow&>(btn.window()).addTaskWindow();
}

void DayWindow::addTaskWindow() {
    AddTaskWindow* task_window = new AddTaskWindow(this);
    this->hide();
}

void DayWindow::closeWindowCB(Graph_lib::Address, Graph_lib::Address pw) {
    MyButton& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<DayWindow&>(btn.window()).hide();
}


DayWindow::DayWindow(int width, int height, Chrono_ns::Date& date, const std::string& day)
    :
Window(BASIC_WINDOW_POSITION, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT, "Day"),
dayName(Graph_lib::Text(Graph_lib::Point(MARGIN, 10+MARGIN), day)),
information(Graph_lib::Text{Graph_lib::Point(200, 10+MARGIN), ""}),
add_task_button(MyButton({width-BUTTON_WIDTH-MARGIN, MARGIN},
    BUTTON_WIDTH, BUTTON_HEIGHT, "add task", addTaskWindowCB)),
close_window_button(MyButton({0, BASIC_WINDOW_HEIGHT-BUTTON_HEIGHT}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Back", closeWindowCB)),
date(date)
{
    size_range(BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT);

    tasks = task_manager.get_tasks(date);

    Graph_lib::Vector_ref<TaskManager_ns::Task> tasks_ref;

    for (auto& task : tasks) {
        TaskManager_ns::Task* new_task = new TaskManager_ns::Task(
            task.name, task.text, task.period
        );
        new_task->set_id(task.get_id());
        tasks_ref.push_back(new_task);

        buttons.push_back(CreateButton(new_task));
        attach(buttons.back());
    }

    int m_day = date.day();
    int month = static_cast<int>(date.month());
    int year = date.year();

    std::string information_about_day = std::to_string(m_day) + "/" + std::to_string(month) + "/" + std::to_string(year);
    information.set_label(information_about_day);

    dayName.set_color(Graph_lib::Color::black);
    dayName.set_font(Graph_lib::Font::helvetica);
    information.set_color(Graph_lib::Color::black);
    information.set_font(Graph_lib::Font::helvetica);
    dayName.set_font_size(font_size);

    attach(dayName);
    attach(add_task_button);
    attach(information);
    attach(close_window_button);
}


MyButton* DayWindow::CreateButton(TaskManager_ns::Task* task) {
    TaskManager_ns::Task* task1 = new TaskManager_ns::Task(
                task->name, task->text, task->period
            );
    task1->set_id(task->get_id());
    MyButton* b = new MyButton({START_BUTTONS_POSITION_X+pos_x, START_BUTTONS_POSITION_Y+pos_y},
        BUTTON_WIDTH, BUTTON_HEIGHT, task1->name, task1, showTaskInfoCB);
    pos_y += BUTTON_HEIGHT;
    if ((buttons.size()+1) % 5 == 0) {
        pos_x += BUTTON_WIDTH + MARGIN;
        pos_y = 10;
    }
    return b;
}


void DayWindow::addTask(TaskManager_ns::Task *task) {
    task_manager.add_task(*task);
    task->set_id(task_manager.get_tasks()[task_manager.get_tasks().size()-1].get_id());
    buttons.push_back(CreateButton(task));
    attach(buttons[buttons.size()-1]);
    task_manager.set_id_to_file();
}

void DayWindow::redrawButtons() {
    pos_x = 50;
    pos_y = 10;
    for (int i = 0; i < buttons.size(); i++) {
        buttons[i].move(-buttons[i].x_coord, -buttons[i].y_coord);
        buttons[i].x_coord = pos_x + START_BUTTONS_POSITION_X;
        buttons[i].y_coord = pos_y + START_BUTTONS_POSITION_Y;
        buttons[i].move(buttons[i].x_coord, buttons[i].y_coord);
        pos_y += BUTTON_HEIGHT;
        if ((i+1) % 5 == 0) {
            pos_x += BUTTON_WIDTH + MARGIN;
            pos_y = 10;
        }
    }
}


void DayWindow::removeTask(TaskManager_ns::Task& task) {
    for (int i = 0; i < buttons.size(); i++) {
        if (buttons[i].task->get_id() == task.get_id()) {
            detach(buttons[i]);
            task_manager.delete_task(task);
            buttons.erase(i);
            break;
        }
    }
    redrawButtons();
}