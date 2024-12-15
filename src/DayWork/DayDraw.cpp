#include "DayDraw.h"

#include "TaskWindow.h"
#include "PARAMETERS.h"
#include "ChangeTaskInfo.h"
#include "MainWindowPart/MainWindow.h"
#include "MainWindowPart/month.h"

std::vector<TaskManager_ns::Task> tasks;
extern TaskManager_ns::TaskManager task_manager;

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
    reinterpret_cast<DayWindow&>(btn.window()).closeWindow();
}

void DayWindow::closeWindow() {
    this->hide();
    if (from_month) {
        month_window->label(month_window->month_name.c_str());
        month_window->show();
    }
    else {
        week_window->label("ToDoList");
        week_window->show();
    }
}


void DayWindow::nextWindowCB(Graph_lib::Address, Graph_lib::Address pw) {
    MyButton& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<DayWindow&>(btn.window()).nextWindow();
}

void DayWindow::nextWindow() {
    int left = current_buttons_window*20;
    int right = std::min(current_buttons_window*20+20, buttons.size());
    for (int i = left; i < right; i++) {
        detach(buttons[i]);
    }
    ++current_buttons_window;
    redrawButtons();
    left = current_buttons_window*20;
    right = std::min(current_buttons_window*20+20, buttons.size());
    if (right - left != 20) {
        detach(next_button);
    }
    attach(prev_button);
}

void DayWindow::prevWindowCB(Graph_lib::Address, Graph_lib::Address pw) {
    MyButton& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<DayWindow&>(btn.window()).prevWindow();
}

void DayWindow::prevWindow() {
    int left = current_buttons_window*20;
    int right = std::min(current_buttons_window*20+20, buttons.size());
    for (int i = left; i < right; i++) {
        detach(buttons[i]);
    }
    --current_buttons_window;
    redrawButtons();
    attach(next_button);
    if (current_buttons_window == 0) {
        detach(prev_button);
    }
}


DayWindow::DayWindow(int width, int height, Chrono_ns::Date& date, const std::string& day, DateButton* datebutton)
    :
Window(BASIC_WINDOW_POSITION, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT, "Day Window"),
dayName(Graph_lib::Text(Graph_lib::Point(MARGIN, 10+MARGIN), day)),
information(Graph_lib::Text{Graph_lib::Point(200, 10+MARGIN), ""}),
add_task_button(MyButton({width-BUTTON_WIDTH-MARGIN, MARGIN},
    BUTTON_WIDTH, BUTTON_HEIGHT, "add task", addTaskWindowCB)),
close_window_button(MyButton({0, BASIC_WINDOW_HEIGHT-BUTTON_HEIGHT}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Back", closeWindowCB)),
next_button(MyButton({BASIC_WINDOW_WIDTH-BUTTON_WIDTH, BASIC_WINDOW_HEIGHT-BUTTON_HEIGHT},
    BUTTON_WIDTH, BUTTON_HEIGHT, "Next", nextWindowCB)),
prev_button(MyButton({BASIC_WINDOW_WIDTH-2*BUTTON_WIDTH, BASIC_WINDOW_HEIGHT-BUTTON_HEIGHT},
    BUTTON_WIDTH, BUTTON_HEIGHT, "Prev", prevWindowCB)),
date(date),
day_from_called(datebutton)
{
    size_range(BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT);

    tasks = task_manager.get_tasks(date);
    std::cout << tasks.size() << '\n';

    Graph_lib::Vector_ref<TaskManager_ns::Task> tasks_ref;

    for (auto& task : tasks) {
        TaskManager_ns::Task* new_task = new TaskManager_ns::Task(
            task.name, task.text, task.period
        );
        new_task->set_id(task.get_id());
        tasks_ref.push_back(new_task);

        buttons.push_back(CreateButton(new_task));
        attach(buttons.back());
        if (buttons.size() > 20) {
            detach(buttons.back());
        }
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

    if (buttons.size() > 20) {
        attach(next_button);
    }
}


MyButton* DayWindow::CreateButton(TaskManager_ns::Task* task) {
    TaskManager_ns::Task* task1 = new TaskManager_ns::Task(
                task->name, task->text, task->period
            );
    task1->set_id(task->get_id());
    MyButton* b = new MyButton({pos_x, pos_y},
        BUTTON_WIDTH, BUTTON_HEIGHT, task1->name, task1, showTaskInfoCB);
    pos_y += BUTTON_HEIGHT;
    if ((buttons.size()+1) % 5 == 0) {
        pos_x += BUTTON_WIDTH + MARGIN;
        pos_y = START_BUTTONS_POSITION_X;
    }
    if ((buttons.size()+1) % 20 == 0) {
        pos_x = START_BUTTONS_POSITION_X;
    }
    return b;
}


void DayWindow::addTask(TaskManager_ns::Task *task) {
    task_manager.add_task(*task);
    task->set_id(task_manager.get_tasks()[task_manager.get_tasks().size()-1].get_id());
    buttons.push_back(CreateButton(task));
    attach(buttons.back());
    if (buttons.size() >= 20) { detach(buttons.back()); }
    if ((buttons.size()-1) % 20 == 0 && buttons.size() > 20) {attach(next_button); }
    redrawButtons();
    task_manager.set_id_to_file();
}

void DayWindow::redrawButtons() {
    pos_x = START_BUTTONS_POSITION_X;
    pos_y = START_BUTTONS_POSITION_Y;
    int left = current_buttons_window*20;
    int right = std::min(current_buttons_window*20+20, buttons.size());
    for (int i = left; i < right; i++) {
        buttons[i].move_to_coordinates(pos_x, pos_y);
        pos_y += BUTTON_HEIGHT;
        if ((i+1) % 5 == 0) {
            pos_x += BUTTON_WIDTH + MARGIN;
            pos_y = START_BUTTONS_POSITION_X;
        }
    }
    if ((buttons.size()+1) % 20 == 0) {
        pos_x = START_BUTTONS_POSITION_X;
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