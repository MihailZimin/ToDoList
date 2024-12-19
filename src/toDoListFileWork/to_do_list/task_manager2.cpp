#include "task_manager.h"
#include "chrono.h"
#include <iostream>
#include <fstream>
#include <cstdio>
#include <sstream>

namespace TaskManager_ns
{

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
        std::ifstream in_id;
        in_id.open("id_counter.txt");
        if(in_id)
        {
            in_id >> counter;
            in_id.close();
        }
        else
            throw std::runtime_error("Can't open file with ids");

        download_tasks();

    }

    void TaskManager::set_id_to_file(){
        std::ofstream out_id("id_counter.txt");
        out_id << counter;
        if(!out_id)
            throw std::runtime_error("Can't add amount of ids to file");
        out_id.close();
    }

    void TaskManager::download_tasks()
    {
        std::cout << "download_tasks()\n";
        using namespace Chrono_ns;

        in.open("tasks.txt");

        if(!in)
            throw std::runtime_error("File isn't open");

        

        std::string line1;
        while (std::getline(in, line1)) {
            unsigned long long id{1};
            int start_hour{1};
            int start_min{1};
            int start_day{1};
            int start_month{1};
            int start_year{1};
            int end_hour{1};
            int end_min{1};
            int end_day{1};
            int end_month{1};
            int end_year{1};
            std::string task_name;
            std::string task_text;

            std::istringstream iss(line1);

            iss >> id >> start_hour >> start_min >> start_day >> start_month >> start_year
                    >> end_hour >> end_min >> end_day >> end_month >> end_year;

            if(!iss)
                throw std::runtime_error("Dowloading tasks is faild");

            Date start_date {start_day, static_cast<Month>(start_month), start_year};
            Date end_date {end_day, static_cast<Month>(end_month), end_year};

            std::string name_line;
            task_name = "";
            std::getline(iss, task_name, ';');
            task_name.erase(task_name.begin());


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
        in.close();
    }


    void TaskManager::add_task(Task task)
    {
        out.open("tasks.txt", std::ios::app);

        std::cout << "add_task()\n";

        if(!out)
            throw std::runtime_error("Can't open file");

        std::cout << task.text << '\n';

        ++counter;
        task.set_id(counter);
        out << task.get_id() << ' ' << task.period.start_hour() << ' ' << task.period.start_min() << ' '
            << task.period.start_date().day() << ' ' << int(task.period.start_date().month()) << ' '
            << task.period.start_date().year() << ' '  << task.period.end_hour() << ' '
            << task.period.end_min() << ' ' << task.period.end_date().day() << ' '
            << int(task.period.end_date().month()) << ' ' << task.period.end_date().year() << ' '
            << task.name << ';' << task.text << std::endl;

        tasks.push_back(task);
        sort_task();
        out.close();
    }

    void TaskManager::delete_task(Task task)
    {
        using namespace Chrono_ns;

<<<<<<< HEAD
        std::ofstream buf_out("buf.txt");
        std::cout << task.get_id() << std::endl;
        for (size_t i = 0; i < tasks.size(); ++i)
=======
        for (size_t i {0}; i < tasks.size(); ++i)
>>>>>>> origin/main
        {
            std::cout << tasks[i].get_id() << " / " << task.get_id() << std::endl;
            if(tasks[i].get_id() == task.get_id())
            {
                tasks.erase(tasks.begin() + i);
<<<<<<< HEAD
                std::cout << "delete_task()\n";
                for (size_t j = 0; j < tasks.size(); ++j)
                {
                    if (tasks[j].get_id() >= task.get_id())
                    {
                        tasks[j].set_id(tasks[j].get_id() - 1);
                    }
                }
=======
>>>>>>> origin/main
                break;
            }
        }

<<<<<<< HEAD
        out.open("tasks.txt", std::ios::trunc);
        out.clear();
        out.seekp(0, std::ios::beg);
        --counter;
        set_id_to_file();
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
=======
        out.open("tasks.txt");
  
        for (Task t : tasks)
        {
            std::string task_text_1 = std::to_string(t.get_id()) + ' ' +
                std::to_string(t.period.start_hour()) + ' ' +
                std::to_string(t.period.start_min()) + ' ' +
                std::to_string(t.period.start_date().day()) + ' ' +
                std::to_string(int(t.period.start_date().month())) + ' ' +
                std::to_string(t.period.start_date().year()) + ' ' +
                std::to_string(t.period.end_hour()) + ' ' +
                std::to_string(t.period.end_min()) + ' ' +
                std::to_string(t.period.end_date().day()) + ' ' +
                std::to_string(int(t.period.end_date().month())) + ' ' +
                std::to_string(t.period.end_date().year()) + ' ' +
                t.name + ';' + t.text;
>>>>>>> origin/main
            out << task_text_1 << '\n';
        }
        if(!out)
            throw std::runtime_error("Buf_out failed on last line");
        out.close();
    }

    void TaskManager::update_task(Task& old_task, Task& new_task)
    {
        size_t start_tasks_lenth {tasks.size()};
        delete_task(old_task);
        if(start_tasks_lenth != tasks.size())
        {
            new_task.set_id(old_task.get_id());

            out.open("tasks.txt", std::ios::app);

            std::cout << "add_task()\n";

            if(!out)
                throw std::runtime_error("Can't open file");

            std::cout << new_task.text << '\n';

            out << new_task.get_id() << ' ' << new_task.period.start_hour() << ' ' << new_task.period.start_min() << ' '
                << new_task.period.start_date().day() << ' ' << int(new_task.period.start_date().month()) << ' '
                << new_task.period.start_date().year() << ' '  << new_task.period.end_hour() << ' '
                << new_task.period.end_min() << ' ' << new_task.period.end_date().day() << ' '
                << int(new_task.period.end_date().month()) << ' ' << new_task.period.end_date().year() << ' '
                << new_task.name << ';' << new_task.text << std::endl;

            tasks.push_back(new_task);
            sort_task();
            out.close();
        }
    }


    void TaskManager::sort_task()
    {
        for (size_t i = 0; i+1 < tasks.size(); ++i)
        {
            for (size_t j = 0; j+1 < tasks.size() - i; ++j)
            {
                if (tasks[j+1].period < tasks[j].period)
                    std::swap(tasks[j], tasks[j+1]);
            }
        }
    }

    void TaskManager::sort_task()
    {
        for (size_t i = 0; i+1 < tasks.size(); ++i)
        {
            for (size_t j = 0; j+1 < tasks.size() - i; ++j)
            {
                if (tasks[j+1].period < tasks[j].period)
                    std::swap(tasks[j], tasks[j+1]);
            }
        }
    }

    std::vector<Task> TaskManager::get_tasks()
    {
        std::cout << "get_tasks()\n";
        return tasks;
    }

    std::vector<Task> TaskManager::get_tasks(Chrono_ns::Date date)
    {
        this->sort_task();
        std::vector<Task> day_tasks;
        for(auto& task : tasks)
        {
            if(date.in_period(task.period))
            {
                day_tasks.push_back(task);
            }
        }
        return day_tasks;
    }
}
