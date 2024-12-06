#include "chrono.h"
#include "task_manager.h"
#include <iostream>

// #include <stdio.h>
// #include "sqlite3.h"

#include <iostream>
#include <fstream>


int main()
try
{
    using namespace Chrono_ns;
    using namespace TaskManager_ns;

    // SQLite
    // char* err_msg;
    // std::string command = "CREATE TABLE IF NOT EXISTS TASKS("
    //                       "START_MIN        INT        NOT NULL"
    //                       "START_HOUR        INT        NOT NULL"
    //                       "START_DAY        INT        NOT NULL"
    //                       "START_MONTH        INT        NOT NULL"
    //                       "START_YEAR       INT        NOT NULL"
    //                       "END_MIN        INT        NOT NULL"
    //                       "END_HOUR        INT        NOT NULL"
    //                       "END_DAY        INT        NOT NULL"
    //                       "END_MONTH        INT        NOT NULL"
    //                       "END_YEAR       INT        NOT NULL"
    //                       "NAME           TEXT    NOT NULL, "
    //                       "TEXT          TEXT     NOT NULL);";
    
    // sqlite3 *db;    // указатель на базу данных
    
    // int result  = sqlite3_open("database.db", &db);// открываем подключение к базе данных

    // if(result != SQLITE_OK) 
    // {
    //     std::cout << "Database error: " << sqlite3_errmsg(db) << std::endl;
    //     sqlite3_close(db);
    //     return -1;
    // }
    
    // sqlite3_exec(db,command.c_str(), 0, 0, &err_msg);
    // if(result != SQLITE_OK) 
    // {
    //     std::cout << "Database error: " << err_msg << std::endl;
    //     sqlite3_free(err_msg); //очищаем память, выделенную под err_msg 
    //     sqlite3_close(db);
    //     return -1;
    // }
    // // закрываем подключение
    // sqlite3_close(db);






    // Month m = Month::oct;
    // std::cout << int(m) << std::endl;
    // ++m;
    // std::cout << int(m) << std::endl;
    // ++m;
    // std::cout << int(m) << std::endl;
    // ++m;
    // std::cout << int(m) << std::endl;
    // ++m;
    // std::cout << int(m) << std::endl;
    // --m;
    // std::cout << int(m) << std::endl;
    // --m;
    // std::cout << int(m) << std::endl;
    // --m;
    // std::cout << int(m) << std::endl;
    // --m;
    // std::cout << int(m) << std::endl;

    // Date d1 (1,Month::jan,2033);
    // Date d2 = d1;
    // Date d0 {1,Month::feb,2033};

    // std::cout << d1.day() << std::endl;
    // std::cout << int(d1.month()) << std::endl;
    // std::cout << d1.year() << std::endl;

    // std::cout << d2.day() << std::endl;
    // std::cout << int(d2.month()) << std::endl;
    // std::cout << d2.year() << std::endl;

    // std::cout << (d2 == d1) << std::endl;
    // std::cout << (d2 != d1) << std::endl;    

    // std::cout << (d2 == d0) << std::endl;
    // std::cout << (d2 != d0) << std::endl;


    // std::cout << is_date(1,Month::jan,2033) << std::endl;
    // Date d3;
    // std::cin >> 



// Period tests
    //Period t1(16,10,Date(1,Month::oct,2023), 19,40, Date(2,Month::oct,2023));
    // Period t2(15,30,Date(3,Month::apr,2024), 17,20, Date(5,Month::mar,2021));
    // Period t3(15,30,Date(3,Month::apr,2024), 17,20,Date(3,Month::may,2024));
    // Period t4(15,30,Date(3,Month::apr,2024), 17,20, Date(5,Month::mar,2021));

    // std::cout << (t2 == t1) << std::endl;
    // std::cout << (t2 != t1) << std::endl;

    // std::cout << (t3 == t1) << std::endl;
    // std::cout << (t3 != t1) << std::endl;

    // std::cout << (t4 == t1) << std::endl;
    // std::cout << (t4 != t1) << std::endl;

    // std::cout << t1.start_hour() << std::endl;
    // std::cout << t1.start_min() << std::endl;
    // std::cout << t1.end_hour() << std::endl;
    // std::cout << t1.end_min() << std::endl;
    // std::cout << t1.start_date() << std::endl;
    // std::cout << t1.end_date() << std::endl;
    
// корректность периода
    // std::cout << is_period(16,10,Date(3,Month::apr,2024), 19,40, Date(3,Month::apr,2024)) << std::endl;
    // std::cout << is_period(19,10,Date(3,Month::apr,2024), 19,10, Date(3,Month::apr,2024)) << std::endl;
    // std::cout << is_period(18,10,Date(3,Month::apr,2024), 17,40, Date(3,Month::apr,2024)) << std::endl;
    // std::cout << is_period(18,10,Date(3,Month::apr,2024), 18,00, Date(3,Month::apr,2024)) << std::endl;

    // //std::cout << t3 << std::endl;
    // std::cout << "\n";

    // std::cout << is_period(16,10,Date(3,Month::apr,2024), 19,40, Date(3,Month::apr,2024)) << std::endl;
    // std::cout << is_period(16,10,Date(4,Month::apr,2024), 19,40, Date(3,Month::apr,2024)) << std::endl;
    // std::cout << is_period(16,10,Date(3,Month::jul,2024), 19,40, Date(3,Month::apr,2024)) << std::endl;
    // std::cout << is_period(16,10,Date(3,Month::apr,2025), 19,40, Date(3,Month::apr,2024)) << std::endl;
    // std::cout << is_period(16,10,Date(5,Month::dec,2022), 19,40, Date(3,Month::apr,2024)) << std::endl;

    // std::cout << "\n";

    // std::cout << is_period(19,10,Date(4,Month::apr,2024), 19,10, Date(3,Month::apr,2024)) << std::endl;
    // std::cout << is_period(19,10,Date(3,Month::apr,2024), 19,10, Date(3,Month::apr,2024)) << std::endl;
    // std::cout << is_period(19,10,Date(3,Month::apr,2025), 19,10, Date(3,Month::apr,2024)) << std::endl;
    // std::cout << is_period(19,10,Date(5,Month::mar,2022), 19,10, Date(3,Month::apr,2024)) << std::endl;
    // std::cout << is_period(19,10,Date(3,Month::mar,2024), 19,10, Date(3,Month::apr,2024)) << std::endl;
    // std::cout << is_period(19,10,Date(3,Month::apr,-2024), 19,10, Date(3,Month::apr,2024)) << std::endl;
    // std::cout << is_period(19,10,Date(1,Month::apr,2024), 19,10, Date(3,Month::apr,2024)) << std::endl;
    // std::cout << is_period(19,10,Date(10,Month::nov,2018), 19,10, Date(3,Month::apr,2024)) << std::endl;
 

// Тест сравнения дат

    // Date d1 {10,Month::feb, 2023};
    // Date d2 {10,Month::feb, 2022};
    // Date d3 {10,Month::feb, 2024};
    // Date d4 {10,Month::jan, 2023};
    // Date d5 {10,Month::mar, 2023};
    // Date d6 {8,Month::feb, 2023};
    // Date d7 {15,Month::feb, 2023};
    // Date d8 {10,Month::feb, 2023};

    // Date d9 {10,Month::apr, 2022};
    // Date d10 {10,Month::jan, 2025};
    // Date d11 {17,Month::apr, 2022};
    // Date d12 {19,Month::feb, 2022};
    // Date d13 {5,Month::jan, 2026};

    // std::cout << (d1 > d2) << std::endl; // false
    // std::cout << (d1 > d3) << std::endl;// true
    // std::cout << (d1 > d4) << std::endl;// false
    // std::cout << (d1 > d5) << std::endl;// true
    // std::cout << (d1 > d6) << std::endl;// false
    // std::cout << (d1 > d7) << std::endl;// true
    // std::cout << (d1 > d8) << std::endl;// false
    // std::cout << (d1 > d9) << std::endl;// false
    // std::cout << (d1 > d10) << std::endl;// true
    // std::cout << (d1 > d11) << std::endl;// false
    // std::cout << (d1 > d12) << std::endl;// false
    // std::cout << (d1 > d13) << std::endl;// true

//test days_in_month()
    //std::cout << days_in_month(2024,Month::apr) << std::endl;


    // TaskManager tests
    // TaskManager tm {};
    // Period p(15,30,Date(12,Month::aug,2024),17,20,Date(12,Month::aug,2025));
    // tm.add_task(Task("Name", "Text", p));
    // std::cout << tm.tasks.size() << std::endl;

// TASK_MANAGER_2
    TaskManager tm{};
    Period p1{15,30,Date(3,Month::apr,2024), 17,20,Date(3,Month::may,2024)};
    Task task1{"Task1", "Text1", p1};
    // std::cout << "0\n";
    // tm.add_task(task1);
    // std::cout << "1\n";
    // Period p2{9,30,Date(7,Month::sep,2022), 17,19,Date(3,Month::feb,2024)};
    // std::cout << "2\n";
    // Task task2{"Task2", "Text2", p2};
    // std::cout << "3\n";
    // tm.add_task(task2);
    // std::cout << "4\n";
    std::vector<Task> tasks_list = tm.get_tasks();
    // std::cout << tasks_list.size() << std::endl;

    // //std::cout << tasks_list[12] << std::endl;

    // for(Task t : tasks_list)
    //     std::cout << t << std::endl;

    //tm.delete_task(task1);
    tasks_list = tm.get_tasks();
    //std::cout << tasks_list[12].get_id() << std::endl;
    //std::vector<Task> tasks_to_del = std::vector<Task> (tasks_list.begin(), tasks_list.end()-5);
    for(int i = 0; i < (tasks_list.size() - 5); ++i)
    {
        std::cout << tasks_list[i].get_id() << std::endl;
        tm.delete_task(tasks_list[i]);
    }

    tasks_list = tm.get_tasks();

    for(Task t : tasks_list)
        std::cout << t << std::endl;

    return 0;
}
catch(std::exception& e){
    std::cerr << e.what() << std::endl;
    return 1;
}
catch(...){
    std::cerr << "Something went wrong..." << std::endl;
    return 2;
}