#include "task_manager.h"
#include "chrono.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <sstream>

namespace TaskManager_ns
{
// Task
    unsigned long long Task::counter {0};
    Task::Task(std::string task_name, std::string task_text, Chrono_ns::Period period)
            : name {task_name}, text {task_text}, period {period}
    {
        if(counter == 0)
        {
            std::ifstream in_id("id_counter.txt", std::ios_base::app);
            in_id.exceptions(in_id.exceptions() | std::ios_base::badbit);
            if(!in_id)
            {
                std::ofstream out_id("id_counter.txt");
                // out_id << counter;
                // if(!out_id)
                //     throw std::runtime_error("Can't add file with ids");
            }
            in_id.open("id_counter.txt");
            if(in_id.is_open())
            {
                in_id >> counter;
                in_id.close();
            }
            else
                throw std::runtime_error("Can't open file with ids");
        }
        ++counter;
        id = counter;

        std::ofstream out_id("id_counter.txt");
        out_id << counter;
        if(!out_id)
            throw std::runtime_error("Can't add amount of ids to file");
        out_id.close();
    }


    std::ostream& operator << (std::ostream& os, const Task& t)
    {
        return os << "Task name: " << t.name << "\nTask period: " << t.period << "\nTask text:\n" << t.text << std::endl;
    }

    bool operator == (const Task& t1, const Task& t2)
    {
        return t1.name == t2.name && t1.text == t2.text && t1.period == t2.period;
    }

    bool operator != (const Task& t1, const Task& t2)
    {
        return !(t1 == t2);
    }

// Task Manager
    TaskManager::TaskManager()
    {
        if(!in.is_open())
        {
            std::ofstream out("tasks.txt", std::ios_base::app);
            out.close();
        }
        std::ifstream in("tasks.txt");
        in.exceptions(in.exceptions() | std::ios_base::badbit);

        if(!in)
            throw std::runtime_error("Can't open file");

        download_tasks();

    }

    //std::istringstream iss;

    void TaskManager::download_tasks()
    {
        std::cout << "download_tasks()\n";
        using namespace Chrono_ns;
        std::string line;

        in.open("tasks.txt", std::ios_base::app);
        in.clear();
        in.seekg(0, std::ios::beg);

        if(!in.is_open())
            throw std::runtime_error("File isn't open");

        unsigned long long id;
        unsigned start_hour;
        unsigned start_min;
        unsigned start_day;
        unsigned start_month;
        int start_year;
        unsigned end_hour;
        unsigned end_min;
        unsigned end_day;
        unsigned end_month;
        int end_year;
        std::string task_name;
        std::string task_text;

        std::string line1;
        while (std::getline(in, line1)) {
            std::istringstream iss(line1);
            iss.clear();
            iss.seekg(0, std::ios::beg);
            iss >> id >> start_hour >> start_min >> start_day >> start_month >> start_year
                    >> end_hour >> end_min >> end_day >> end_month >> end_year >> task_name;

            Date start_date {start_day, static_cast<Month>(start_month), start_year};
            Date end_date {end_day, static_cast<Month>(end_month), end_year};

            std::string line2;
            task_text = "";
            while (iss >> line2) {
                task_text += line2 + ' ';
            }
            task_text.pop_back();

            Period p {start_hour, start_min, start_date, end_hour, end_min, end_date};
            Task t {task_name, task_text, p};
            t.set_id(id);
            tasks.push_back(t);
        }
        if(in.eof())
            return;
        if(in.fail()) {
            throw std::runtime_error("Uncorrect data in file");
        }
        // if(in.bad())
            // throw std::runtime_error("Ifstream \"in\" is damaged");

        in.close();
    }


    void TaskManager::add_task(Task task) // ПОПРОБУЙ СДЕЛАТЬ ТАК, ЧТОБЫ ЗАДАЧИ ДОБАВЛЯЛИСЬ УЖЕ В НУЖНОМ ПОРЯДККЕ (ЧТОБЫ НЕ СОРТИРОВАТЬ ИХ)
    {
        out.open("tasks.txt", std::ios::app);
        out.clear();
        out.seekp(0, std::ios::end);

        std::cout << "add_task()\n";

        if(!out)
            throw std::runtime_error("Can't get access to file");
        if(!out.is_open())
            throw std::runtime_error("Can't open file");

        std::cout << task.text << '\n';

        out << task.get_id() << ' ' << task.period.start_hour() << ' ' << task.period.start_min() << ' '
            << task.period.start_date().day() << ' ' << int(task.period.start_date().month()) << ' '
            << task.period.start_date().year() << ' '  << task.period.end_hour() << ' '
            << task.period.end_min() << ' ' << task.period.end_date().day() << ' '
            << int(task.period.end_date().month()) << ' ' << task.period.end_date().year() << ' '
            << task.name << ' ' << task.text << std::endl;

        tasks.push_back(task);
        out.close();
    }

    void TaskManager::delete_task(Task task) // пожалуй, лучше ввести id у задач
    {                                        // МОЖНО ПОЛУЧАТЬ ИЗ ФАЙЛА СТРОКИ, А НЕ ПО ЭЛЕМЕНТАМ ВСЁ.
        using namespace Chrono_ns;           // СООТВЕТСТВЕННО И ПЕРЕЗАПИСЫВАТЬ СТРОКАМИ     !!!!!!

        std::ofstream buf_out("buf.txt");
        std::cout << "delete_task()\n";

        for (size_t i {0}; i < tasks.size(); ++i)
        {
            if(tasks[i].get_id() == task.get_id()) {
                tasks.erase(tasks.begin() + i);
                break;
            }
        }

        out.open("tasks.txt", std::ios::trunc);
        out.clear();
        out.seekp(0, std::ios::beg);
        for (int i = 0; i < tasks.size(); ++i) {
            task = tasks[i];
            std::string task_text_1 = std::to_string(task.get_id()) + ' ' +
                std::to_string(task.period.start_hour()) + ' ' +
                std::to_string(task.period.start_min()) + ' ' +
                std::to_string(task.period.start_date().day()) + ' ' +
                std::to_string(static_cast<int>(task.period.start_date().month())) + ' ' +
                std::to_string(task.period.start_date().year()) + ' ' +
                std::to_string(task.period.end_hour()) + ' ' +
                std::to_string(task.period.end_min()) + ' ' +
                std::to_string(task.period.end_date().day()) + ' ' +
                std::to_string(static_cast<int>(task.period.end_date().month())) + ' ' +
                std::to_string(task.period.end_date().year()) + ' ' +
                task.name + ' ' + task.text;
            out << task_text_1 << '\n';
        }
        if(!out)
            throw std::runtime_error("Buf_out failed on last line");
        out.close();
    }



    void TaskManager::update_task(Task old_task, Task new_task)
    {
        std::ofstream buf_out("buf.txt");
        std::cout << "update_task()\n";

        if(!buf_out)
            throw std::runtime_error("Can't open buffer file");

        in.open("tasks.txt");
        in.clear();
        in.seekg(0, std::ios_base::beg);

        if(!in.is_open())
            throw std::runtime_error("File with tasks isn't open");

        std::string line;
        int i {1};
        // if(getline(in, line))
        //     std::cout << "is successful\n";

        std::cout << "old id = " << old_task.get_id() << std::endl;
        while(getline(in, line))
        {
            std::cout << line << std::endl;
            std::cout << line[0] << std::endl;
            if(line[0] == old_task.get_id())
            {
                std::cout << "equal id" << std::endl;
                line = (std::to_string(new_task.get_id()) + ' '
                    + std::to_string(new_task.period.start_hour()) + ' '
                    + std::to_string(new_task.period.start_min()) + ' '
                    + std::to_string(new_task.period.start_date().day()) + ' '
                    + std::to_string(int(new_task.period.start_date().month())) + ' '
                    + std::to_string(new_task.period.start_date().year()) + ' '
                    + std::to_string(new_task.period.end_hour()) + ' '
                    + std::to_string(new_task.period.end_min()) + ' '
                    + std::to_string(new_task.period.end_date().day()) + ' '
                    + std::to_string(int(new_task.period.end_date().month())) + ' '
                    + std::to_string(new_task.period.end_date().year()) + ' '
                    + new_task.name + ' ' + new_task.text);
            }
            buf_out << line << '\n';
            if(!buf_out)
                throw std::runtime_error("Buf_out failed during updating file");
            ++i;
        }
        buf_out.close();
        if(in.eof())
        {
            in.close();
            std::ifstream buf_in("buf.txt");
            out.open("tasks.txt");
            out.clear();
            out.seekp(0, std::ios::beg);
            // добавить проверку открытости файла
            while(getline(buf_in, line))
            {
                out << line << '\n';
                if(!out)
                    throw std::runtime_error("Out failed during updating file");
            }
            out.close();
            if(buf_in.eof())
                buf_in.close();

            if(buf_in.fail())
                throw std::runtime_error("2Uncorrect data in buffer file");
        }
        if(in.fail())
            throw std::runtime_error("1Uncorrect data in file");
    }

    std::vector<Task> TaskManager::get_tasks() const
    {
        std::cout << "get_tasks()\n";
        std::cout << "vector size: " << tasks.size() << std::endl;
        return tasks;
    }

    std::vector<Task> TaskManager::get_tasks(Chrono_ns::Date date) const
    {
        std::vector<Task> day_tasks;
        for(Task task : tasks)
        {
            if(date.in_period(task.period))
            {
                day_tasks.push_back(task);
            }
        }
        return day_tasks;
    }
}
