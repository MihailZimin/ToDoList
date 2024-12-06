#include <iostream>
#include <vector>
#include <string>

#include "Graph_lib/Window.h"
#include "Graph_lib/GUI.h"
#include "Graph_lib/Graph.h"
#include "Graph_lib/Window.h"
#include "Graph_lib/GUI.h"


#include "DayLogic.h"
#include "DayDraw.h"
#include "PARAMETERS.h"

int main() {
    try {
        std::string s1 = "01:21";
        std::string s2 = "01:21";
        Task t1(s1, s2);
        // Task t2("02:21", "Details about the task");
        // Task t3("03:21", "Details about the task");
        Day day;
        day.addTask(&t1);
        // day.addTask(t2);
        // day.addTask(t3);
        DayWindow* day_window = new DayWindow(day, BASIC_WINDOW_WIDTH, BASIC_WINDOW_HEIGHT);
        return Graph_lib::gui_main();
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}