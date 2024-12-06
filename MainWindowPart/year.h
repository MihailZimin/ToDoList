#include "month.h"

using namespace Graph_lib;

class Year: public Graph_lib::Window
{
    public:
        Year(Point xy, int h, int w, int year_number);
        void month_page();
        void main_page_back();
        void year();
        static void year_cb(Address, Address);
        static void main_page_cb(Address, Address);
    private:
        int year_number;
        std::vector<Month> months;
        Button* year_button;
        Button main_page;
};