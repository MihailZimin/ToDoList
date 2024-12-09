//
// Created by Misha on 21.11.2024.
//

#include "DayDraw.h"
#include "TaskWindow.h"
std::vector<TaskManager_ns::Task> tasks;

void DayWindow::showTaskInfoCB(Graph_lib::Address, Graph_lib::Address pw) {
    MyButton& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<DayWindow&>(btn.window()).showTaskInfoWindow(btn);
}

void DayWindow::showTaskInfoWindow(MyButton& btn) {
    TaskWindow* task_window = new TaskWindow(&btn, this);
    this->need_to_be_destroyed = false;
    this->hide();
}

void DayWindow::addTaskCB(Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<DayWindow&>(btn.window()).addTaskWindow(btn);
}

void DayWindow::addTaskWindow(MyButton &btn) {
    AddTaskWindow* task_window = new AddTaskWindow(&btn, this);
    this->need_to_be_destroyed = false;
    this->hide();
}

void DayWindow::closeWindowCB(Graph_lib::Address, Graph_lib::Address pw) {
    MyButton& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<DayWindow&>(btn.window()).hide();
}


DayWindow::DayWindow(int width, int height, Chrono_ns::Date& date, const std::string& day)
    :
Window(BASIC_WINDOW_POSITION, width, height, "Day"),
dayName(Graph_lib::Point(MARGIN, 10+MARGIN), day),
add_task_button(new MyButton({width-BUTTON_WIDTH-MARGIN, MARGIN},
    BUTTON_WIDTH, BUTTON_HEIGHT, "add task", addTaskCB)),
close_window_button(new MyButton({0, BASIC_WINDOW_HEIGHT-BUTTON_HEIGHT}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Back", closeWindowCB)),
date(date)
{
    //tasks = task_manager.get_tasks();
    tasks = task_manager.get_tasks(date);

    std::cout << tasks.size() << '\n';
    Graph_lib::Vector_ref<TaskManager_ns::Task> tasks_ref;
    for (int i = 0; i < tasks.size(); i++) {
        tasks_ref.push_back(tasks[i]);
    }
    for (int i = 0; i < tasks_ref.size(); i++) {
        buttons.push_back(CreateButton(tasks_ref[i]));
    }
    std::cout << buttons.size() << std::endl;
    for (int i = 0; i < buttons.size(); i++) {
        attach(buttons[i]);
    }
    int m_day = date.day();
    int month = static_cast<int>(date.month());
    int year = date.year();
    std::string information_about_day = std::to_string(m_day) + "/" + std::to_string(month) + "/" + std::to_string(year);
    information = new Graph_lib::Text{Graph_lib::Point(200, 10+MARGIN), information_about_day};
    dayName.set_color(Graph_lib::Color::cyan);
    dayName.set_font(Graph_lib::Font::helvetica);
    information->set_color(Graph_lib::Color::black);
    information->set_font(Graph_lib::Font::helvetica);
    dayName.set_font_size(font_size);
    attach(dayName);
    attach(*add_task_button);
    attach(*information);
    attach(*close_window_button);
}


MyButton* DayWindow::CreateButton(TaskManager_ns::Task& task) {
    MyButton* b = new MyButton({START_BUTTONS_POSITION_X+pos_x, START_BUTTONS_POSITION_Y+pos_y},
        BUTTON_WIDTH, BUTTON_HEIGHT, task.name, &task, showTaskInfoCB);
    pos_y += BUTTON_HEIGHT;
    if ((buttons.size()+1) % 10 == 0) {
        pos_x += BUTTON_WIDTH + MARGIN;
        pos_y = 10;
    }
    return b;
}

// void DayWindow::SetLabel(TaskManager_ns::Task *task) {
//     for (int i = 0; i < buttons.size(); i++) {
//         if (buttons[i].task == task) {
//             buttons[i].label = task->name;
//         }
//     }
// }

void DayWindow::addTask(TaskManager_ns::Task *task) {
    buttons.push_back(CreateButton(*task));
    attach(buttons[buttons.size()-1]);
    std::cout << "attached" << '\n';
    task_manager.add_task(*task);
}

void DayWindow::RedrawButtons() {
    pos_x = 50;
    pos_y = 10;
    for (int i = 0; i < buttons.size(); i++) {
        buttons[i].move(-buttons[i].x_coord, -buttons[i].y_coord);
        buttons[i].x_coord = pos_x + START_BUTTONS_POSITION_X;
        buttons[i].y_coord = pos_y + START_BUTTONS_POSITION_Y;
        buttons[i].move(buttons[i].x_coord, buttons[i].y_coord);
        pos_y += BUTTON_HEIGHT;
        if ((i+1) % 10 == 0) {
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
    RedrawButtons();
}