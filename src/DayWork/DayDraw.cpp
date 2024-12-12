//
// Created by Misha on 21.11.2024.
//

#include "DayDraw.h"

#include "NoteWindow.h"
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

void DayWindow::openNotesCB(Graph_lib::Address, Graph_lib::Address pw) {
    MyButton& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<DayWindow&>(btn.window()).openNotes();
}

void DayWindow::openNotes() {
    NoteWindow* note_window = new NoteWindow(this);
    this->need_to_be_destroyed = false;
    this->hide();
}

// void DayWindow::NextDayWindowCB(Graph_lib::Address, Graph_lib::Address pw) {
//     auto& btn = Graph_lib::reference_to<MyButton>(pw);
//     reinterpret_cast<DayWindow&>(btn.window()).NextDayWindow();
// }
//
// void DayWindow::NextDayWindow() {
//     if (lowest_index + 20 >= buttons.size()) return;
//     pos_x = 50;
//     pos_y = 10;
//     for (int i = lowest_index; i < highest_index; i++) {
//         detach(buttons[i]);
//     }
//     lowest_index += 20;
//     highest_index = std::min(highest_index+20, buttons.size());
//     for (int i = lowest_index; i < highest_index; i++) {
//         // buttons[i].move(-buttons[i].x_coord, -buttons[i].y_coord);
//         // buttons[i].x_coord = pos_x + START_BUTTONS_POSITION_X;
//         // buttons[i].y_coord = pos_y + START_BUTTONS_POSITION_Y;
//         // buttons[i].move(buttons[i].x_coord, buttons[i].y_coord);
//         pos_y += BUTTON_HEIGHT;
//         if ((i+1) % 5 == 0) {
//             pos_x += BUTTON_WIDTH + MARGIN;
//             pos_y = 10;
//         }
//     }
// }
//
//
// void DayWindow::PrevDayWindowCB(Graph_lib::Address, Graph_lib::Address pw) {
//     auto& btn = Graph_lib::reference_to<MyButton>(pw);
//     reinterpret_cast<DayWindow&>(btn.window()).PrevDayWindow();
// }
//
//
// void DayWindow::PrevDayWindow() {
//     if (highest_index - 20 <= 0) return;
//     pos_x = 50;
//     pos_y = 10;
//     for (int i = lowest_index; i < highest_index; i++) {
//         detach(buttons[i]);
//     }
//     lowest_index -= 20;
//     highest_index -= std::min(20, buttons.size() - highest_index);
//     for (int i = lowest_index; i < highest_index; i++) {
//         buttons[i].move(-buttons[i].x_coord, -buttons[i].y_coord);
//         buttons[i].x_coord = pos_x + START_BUTTONS_POSITION_X;
//         buttons[i].y_coord = pos_y + START_BUTTONS_POSITION_Y;
//         buttons[i].move(buttons[i].x_coord, buttons[i].y_coord);
//         pos_y += BUTTON_HEIGHT;
//         if ((i+1) % 5 == 0) {
//             pos_x += BUTTON_WIDTH + MARGIN;
//             pos_y = 10;
//         }
//     }
// }


DayWindow::DayWindow(int width, int height, Chrono_ns::Date& date, const std::string& day)
    :
Window(BASIC_WINDOW_POSITION, width, height, "Day"),
dayName(Graph_lib::Point(MARGIN, 10+MARGIN), day),
add_task_button(new MyButton({width-BUTTON_WIDTH-MARGIN, MARGIN},
    BUTTON_WIDTH, BUTTON_HEIGHT, "add task", addTaskCB)),
close_window_button(new MyButton({0, BASIC_WINDOW_HEIGHT-BUTTON_HEIGHT}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Back", closeWindowCB)),
date(date),
note_window_button(new MyButton({BASIC_WINDOW_WIDTH-BUTTON_WIDTH-MARGIN,
    BUTTON_HEIGHT + MARGIN}, BUTTON_WIDTH, BUTTON_HEIGHT,
    "NOTE", openNotesCB))
// next_day_window_button(new MyButton({BASIC_WINDOW_WIDTH-BUTTON_WIDTH, BASIC_WINDOW_HEIGHT-BUTTON_HEIGHT},
//     BUTTON_WIDTH, BUTTON_HEIGHT, "Next", NextDayWindowCB)),
// prev_day_window_button(new MyButton({BASIC_WINDOW_WIDTH-2*BUTTON_WIDTH, BASIC_WINDOW_HEIGHT-BUTTON_HEIGHT},
//     BUTTON_WIDTH, BUTTON_HEIGHT, "Prev", PrevDayWindowCB))
{
    tasks = task_manager.get_tasks(date);

    std::cout << tasks.size() << '\n';
    Graph_lib::Vector_ref<TaskManager_ns::Task> tasks_ref;
    for (int i = 0; i < tasks.size(); i++) {
        tasks_ref.push_back(tasks[i]);
    }
    for (int i = 0; i < tasks_ref.size(); i++) {
        buttons.push_back(CreateButton(tasks_ref[i]));
    }

    highest_index = std::min(20, buttons.size());
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
    attach(*note_window_button);
    // attach(*next_day_window_button);
    // attach(*prev_day_window_button);
}


MyButton* DayWindow::CreateButton(TaskManager_ns::Task& task) {
    MyButton* b = new MyButton({START_BUTTONS_POSITION_X+pos_x, START_BUTTONS_POSITION_Y+pos_y},
        BUTTON_WIDTH, BUTTON_HEIGHT, task.name, &task, showTaskInfoCB);
    pos_y += BUTTON_HEIGHT;
    if ((buttons.size()+1) % 5 == 0) {
        pos_x += BUTTON_WIDTH + MARGIN;
        if (pos_x >= START_BUTTONS_POSITION_X + 4 * (BUTTON_WIDTH + MARGIN)) {
            pos_x = 50;
        }
        pos_y = 10;
    }
    return b;
}


void DayWindow::addTask(TaskManager_ns::Task *task) {
    buttons.push_back(CreateButton(*task));
    std::cout << "attached" << '\n';
    task_manager.add_task(*task);
    attach(buttons[buttons.size()-1]);
    task_manager.set_id_to_file();
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
    RedrawButtons();
}