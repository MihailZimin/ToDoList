#include "date_button.h"
#include <map>
#include <ctime>
#include <string>

std::string DateButton::get_day_of_week(int day, const std::string& month, int year) {
    std::map<std::string, int> month_map = {
        {"January", 1}, {"February", 2}, {"March", 3},
        {"April", 4}, {"May", 5}, {"June", 6},
        {"July", 7}, {"August", 8}, {"September", 9},
        {"October", 10}, {"November", 11}, {"December", 12}
    };

    int m = month_map[month];

    std::tm time_in = {0}; 

    time_in.tm_year = year - 1900; 
    time_in.tm_mon = m - 1;        
    time_in.tm_mday = day;

    std::time_t time_temp = std::mktime(&time_in);

    int day_of_week = std::localtime(&time_temp)->tm_wday;

    std::vector<std::string> days = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

    return days[day_of_week];
}