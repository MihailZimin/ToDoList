//
// Created by Misha on 19.11.2024.
//

#ifndef DAY_H
#define DAY_H


#include <vector>
#include <string>
#include "toDoListFileWork/to_do_list/task_manager.h"


// class Task {
// public:
//     std::string name;
//     std::string details;
//
//     Task(std::string& name, std::string& details) : name(name), details(details) {}
//     Task() = default;
// };


class Day {
public:
    void addTask(TaskManager_ns::Task* task);

    std::string& getName();

    void removeTask(int index);

    TaskManager_ns::Task& getTask(int index);

    int getTaskCount() const;

private:
    std::vector<TaskManager_ns::Task*> tasks;
    std::string name{"Monday"};
    //std::string time;
};


#endif //DAY_H
