#ifndef TASK_MANAGER
#define TASK_MANAGER

#include <vector>
#include <string>
#include "chrono.h"

#include <fstream>

// #include <stdio.h>
// #include "sqlite3.h"


namespace TaskManager_ns
{
    struct Task{
        Task(std::string task_name, std::string task_text, Chrono_ns::Period period);
        
        std::string name {"My note"};
        std::string text;
        Chrono_ns::Period period;
        unsigned long long get_id() { return id; }
        void set_id(unsigned long long i_d){ id = i_d; }

        private:
            static unsigned long long counter;
            unsigned long long id;
            
    };


    std::ostream& operator << (std::ostream& os, const Task& t);
    bool operator == (const Task& t1, const Task& t2);
    bool operator != (const Task& t1, const Task& t2);


    class TaskManager{

    public:
        TaskManager();
        //~TaskManager();
        void add_task(Task task);
        void delete_task(Task task);
        // void remove_task(Task task) const;
        // void edit_task(Task prev_task, Task new_task) const;

        std::vector<Task> get_tasks() const;

        
    private:
        std::vector<Task> tasks;
        //sqlite3 *db;    // указатель на базу данных
        std::ifstream in;
        std::ofstream out;

        unsigned long long id_amount;

        void download_tasks();
    };



    int upload_tasks(void *notUsed, int colCount, char **columns, char **colNames);

}


#endif //TASK_MANAGER