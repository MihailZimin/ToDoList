//
// Created by Misha on 21.11.2024.
//

#include "DayLogic.h"


void Day::addTask(TaskManager_ns::Task* task) {
    tasks.push_back(task);
}

std::string& Day::getName() {
    return name;
}

void Day::removeTask(int index) {
    if (index >= 0 && index < tasks.size()) {
        tasks.erase(tasks.begin() + index);
    }
}

TaskManager_ns::Task& Day::getTask(int index) {
    if (index >= 0 && index < tasks.size()) {
        return *tasks[index];
    }
    throw std::out_of_range("Index out of range");
}

int Day::getTaskCount() const {
    return tasks.size();
}