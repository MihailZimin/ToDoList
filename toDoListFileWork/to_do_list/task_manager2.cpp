#include "task_manager.h"
#include "chrono.h"
#include <iostream>
#include <fstream>
#include <cstdio>

namespace TaskManager_ns
{   
// Task
    unsigned long long Task::counter {0};
    Task::Task(std::string task_name, std::string task_text, Chrono_ns::Period period)
            : name {task_name}, text {task_text}, period {period}
    {
        if(counter == 0)
        {
            std::ifstream in_id("id_counter.txt");
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

        in.open("tasks.txt");

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
        
        while(in >> id >> start_hour >> start_min >> start_day >> start_month >> start_year
                    >> end_hour >> end_min >> end_day >> end_month >> end_year >> task_name >> task_text)
        {
            Date start_date {start_day, static_cast<Month>(start_month), start_year};
            Date end_date {end_day, static_cast<Month>(end_month), end_year};

            Period p {start_hour, start_min, start_date, end_hour, end_min, end_date};
            Task t {task_name, task_text, p};
            t.set_id(id);
            tasks.push_back(t);
        }
        if(in.eof())
            return;
        if(in.fail())
            throw std::runtime_error("Uncorrect data in file");
        // if(in.bad())
            // throw std::runtime_error("Ifstream \"in\" is damaged");

        in.close();
    }


    void TaskManager::add_task(Task task) // ПОПРОБУЙ СДЕЛАТЬ ТАК, ЧТОБЫ ЗАДАЧИ ДОБАВЛЯЛИСЬ УЖЕ В НУЖНОМ ПОРЯДККЕ (ЧТОБЫ НЕ СОРТИРОВАТЬ ИХ)
    {
        out.open("tasks.txt", std::ios::app);
        std::cout << "add_task()\n";

        if(!out)
            throw std::runtime_error("Can't get access to file");
        if(!out.is_open())
            throw std::runtime_error("Can't open file");

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
    {
        using namespace Chrono_ns;

        std::ofstream buf_out("buf.txt");
        std::cout << "delete_task()\n";

        if(!buf_out)
            throw std::runtime_error("Can't open buffer file");

        in.open("tasks.txt");
        in.clear();
        in.seekg(0, std::ios_base::beg);

        std::string line;
        if(std::getline(in, line))
        {
            std::cout << line << std::endl;
        }

        if(!in.is_open())
            throw std::runtime_error("File with tasks isn't open");

        bool task_in_list {false};

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
        
       
        
        while(in >> id >> start_hour >> start_min >> start_day >> start_month >> start_year
                    >> end_hour >> end_min >> end_day >> end_month >> end_year >> task_name >> task_text)
        {
            std::cout << "In delete().while\n";
            // Вариант без id у класса Task
            // if(start_hour != task.period.start_hour()
            //         || start_min != task.period.start_min()
            //         || start_day != task.period.start_date().day()
            //         || start_month != unsigned(task.period.start_date().month())
            //         || start_year != task.period.start_date().year()
            //         || end_hour != task.period.end_hour()
            //         || end_min != task.period.end_min()
            //         || start_day != task.period.end_date().day()
            //         || start_month != unsigned(task.period.end_date().month())
            //         || start_year != task.period.end_date().year()
            //         || task_name != task.name
            //         || task_text != task.text
            //         )

            if(task.get_id() == id)
            {
                task_in_list = true;
                continue;
            }
                

            if(!buf_out)
                throw std::runtime_error("Out failed");

            buf_out << id << ' ' << start_hour << ' ' << start_min << ' '
                << start_day << ' ' << start_month << ' '
                << start_year << ' '  << end_hour << ' ' 
                << end_min << ' ' << end_day << ' '
                << end_month << ' ' << end_year << ' '
                << task_name << ' ' << task_text << std::endl;

            for (unsigned i {0}; i < tasks.size(); ++i)
            {
                if(tasks[i] == task)
                    tasks.erase(tasks.begin() + i);
            }
        }

        if(!task_in_list)
            throw std::runtime_error("There is't the task in list");

        if(in.eof())
            return;
        if(in.fail())
            throw std::runtime_error("Uncorrect data in file");

        in.close();
        buf_out.close();

        int exit = rename("buf.txt", "tasks.txt");
        if(!exit)
            throw std::runtime_error("File with tasks not updated");
    }

    std::vector<Task> TaskManager::get_tasks() const
    {
        std::cout << "get_tasks()\n";
        std::cout << "vector size: " << tasks.size() << std::endl;
        return tasks;
    }
}
