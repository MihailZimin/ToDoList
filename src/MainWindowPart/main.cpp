#include "MainWindow.h"

TaskManager_ns::TaskManager task_manager;

int main()
{
    WeekWindow week{Point{100,100}, 400, 600};
    return gui_main();
}
