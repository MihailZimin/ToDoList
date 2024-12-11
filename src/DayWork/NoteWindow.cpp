//
// Created by Misha on 11.12.2024.
//

#include <DayWork/NoteWindow.h>

#include "ChangeTaskInfo.h"
#include "PARAMETERS.h"




void NoteWindow::GoBackCB(Graph_lib::Address, Graph_lib::Address pw) {
    auto& btn = Graph_lib::reference_to<MyButton>(pw);
    reinterpret_cast<NoteWindow&>(btn.window()).goBack();
}

void NoteWindow::goBack() {
    this->hide();
    day_window->show();
}


NoteWindow::NoteWindow(DayWindow* day_window):
day_window(day_window),
    Window(BASIC_WINDOW_POSITION, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT, ""),
go_back(new MyButton({0, BASIC_WINDOW_HEIGHT-BUTTON_HEIGHT}, BUTTON_WIDTH+30, BUTTON_HEIGHT,
    "Back", GoBackCB)),
Note0(new Graph_lib::Text(Graph_lib::Point{MARGIN, MARGIN}, NOTE0)),
Note1(new Graph_lib::Text(Graph_lib::Point{MARGIN, MARGIN+NOTES_SIZE}, NOTE1)),
Note2(new Graph_lib::Text(Graph_lib::Point{MARGIN, MARGIN+NOTES_SIZE*2}, NOTE2)),
Note3(new Graph_lib::Text(Graph_lib::Point{MARGIN, MARGIN+NOTES_SIZE*3}, NOTE3)),
Note4(new Graph_lib::Text(Graph_lib::Point{MARGIN, MARGIN+NOTES_SIZE*4}, NOTE4)),
Note5(new Graph_lib::Text(Graph_lib::Point{MARGIN, MARGIN+NOTES_SIZE*5}, NOTE5)),
Note6(new Graph_lib::Text(Graph_lib::Point{MARGIN, MARGIN+NOTES_SIZE*6}, NOTE6))
{
    attach(*go_back);
    attach(*Note0);
    attach(*Note1);
    attach(*Note2);
    attach(*Note3);
    attach(*Note4);
    attach(*Note5);
    attach(*Note6);
}

