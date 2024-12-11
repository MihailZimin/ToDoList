//
// Created by Misha on 11.12.2024.
//

#ifndef NOTEWINDOW_H
#define NOTEWINDOW_H
#include <Graph_lib/GUI.h>
#include <Graph_lib/Window.h>

#include "MyButton.h"


class NoteWindow: public Graph_lib::Window {
public:
    NoteWindow(DayWindow* task_window);

    static void GoBackCB(Graph_lib::Address, Graph_lib::Address pw);

    void goBack();

    MyButton* go_back;

    DayWindow* day_window;
    Graph_lib::Text* Note0;
    Graph_lib::Text* Note1;
    Graph_lib::Text* Note2;
    Graph_lib::Text* Note3;
    Graph_lib::Text* Note4;
    Graph_lib::Text* Note5;
    Graph_lib::Text* Note6;
    // Graph_lib::Text* Note7;
    // Graph_lib::Text* Note8;
    // Graph_lib::Text* Note9;

    void hide() override {
        Window::hide();
    }
};

#endif //NOTEWINDOW_H