//
// Created by Misha on 19.11.2024.
//

#ifndef DAY_H
#define DAY_H

#include <iostream>
#include <vector>
#include <string>


class Task {
public:
    std::string name;
    std::string details;

    Task(std::string& name, std::string& details) : name(name), details(details) {}
    Task() = default;
};


class Day {
public:
    void addTask(Task* task);

    std::string& getName();

    void removeTask(int index);

    Task& getTask(int index);

    int getTaskCount() const;

private:
    std::vector<Task*> tasks;
    std::string name{"Monday"};
    //std::string time;
};


#endif //DAY_H
