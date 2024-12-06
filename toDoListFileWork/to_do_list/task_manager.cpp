#include "task_manager.h"
#include "chrono.h"
#include <iostream>

#include <stdio.h>
#include "sqlite3.h"


//using namespace TaskManager_ns;
namespace TaskManager_ns
{
    int upload_tasks(void *notUsed, int colCount, char **columns, char **colNames)
    {
        using namespace Chrono_ns;
        for (int i = 0; i < colCount; i++)
        {
            // Date start_date {columns[i]}; // (*columns)[]
            // Date end_date {};
            // Period p
            // Task t {}
            // printf("%s = %s\n", colNames[i], columns[i] ? columns[i] : "NULL");
            std::cout << columns[i] << std::endl;
        }
        // printf("\n");
        return 0;
    }

    TaskManager::TaskManager()
    {

        char* err_msg;
        
        int exit  = sqlite3_open("database.db", &db);// открываем подключение к базе данных

        if(exit != SQLITE_OK) 
        {
            std::cerr << "Database error: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            throw std::runtime_error("Creating database is failed");
        }

        std::string command = "CREATE TABLE IF NOT EXISTS TASKS("
                            "START_HOUR        INT        NOT NULL, "
                            "START_MIN         INT        NOT NULL, "
                            "START_DAY        INT        NOT NULL, "
                            "START_MONTH        INT        NOT NULL, "
                            "START_YEAR       INT        NOT NULL, "
                            "END_HOUR        INT        NOT NULL, "
                            "END_MIN        INT        NOT NULL, "
                            "END_DAY        INT        NOT NULL, "
                            "END_MONTH        INT        NOT NULL, "
                            "END_YEAR       INT        NOT NULL, "
                            "NAME           TEXT    NOT NULL, "
                            "TEXT          TEXT     );";
        std::cout << command << std::endl;
        sqlite3_exec(db,command.c_str(), 0, 0, &err_msg);
        if(exit != SQLITE_OK) 
        {
            std::cerr << "Database error: " << err_msg << std::endl;
            sqlite3_free(err_msg); //очищаем память, выделенную под err_msg 
            sqlite3_close(db);
            throw std::runtime_error("Creating table is failed");
            //throw std::runtime_error(err_msg);
        }

        command = "SELECT * FROM TASKS";
        exit = sqlite3_exec(db, command.c_str(), upload_tasks, 0, &err_msg);
        if(exit != SQLITE_OK) 
        {
            std::cerr << "Database error: " << err_msg << std::endl;
            sqlite3_free(err_msg); //очищаем память, выделенную под err_msg 
            sqlite3_close(db);
            throw std::runtime_error("Uploading data from table is failed");
            //throw std::runtime_error(err_msg);
        }
    }
    // TaskManager::~TaskManager()
    // {
    //     // закрываем подключение
    //     sqlite3_close(db);
    // }

    
    void TaskManager::add_task(Task task)
    {
        
        char* err_msg;
        std::string command = "INSERT INTO TASKS VALUES(" + std::to_string(task.period.start_hour()) + 
        ',' + std::to_string(task.period.start_min()) + ',' + std::to_string(task.period.start_date().day()) +
        ',' + std::to_string(int(task.period.start_date().month())) + ',' + std::to_string(task.period.start_date().year()) +
        ',' + std::to_string(task.period.end_hour()) + ',' + std::to_string(task.period.end_min()) +
        ',' + std::to_string(task.period.end_date().day()) + ',' + std::to_string(int(task.period.end_date().month())) +
        ',' + std::to_string(task.period.end_date().year()) + ',' + task.name + ',' + task.text + ");";
        int exit = sqlite3_exec(db, command.c_str(), 0, 0, &err_msg);
        if (exit != SQLITE_OK )
        {
            std::cerr << "Database error: " << err_msg << std::endl;
            sqlite3_free(err_msg);
            sqlite3_close(db);
            throw std::runtime_error("Insertation to table is failed");
        }
        tasks.push_back(task);
    }



}