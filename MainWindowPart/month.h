#include "day.h"

class Month
{
    public:
        Month(std::string name, Button* month);
        void days_page();
        static void month_cb();
        Button* month_button;
    private:
        std::string month_name; 
        std::vector<Day> days;
};