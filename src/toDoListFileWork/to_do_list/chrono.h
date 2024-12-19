#ifndef CHRONO
#define CHRONO

#include <string>
#include <vector>

namespace Chrono_ns
{
// Time
    class Time
    {
    public:
        Time() = delete;
        Time(int hours, int mins);

        int get_hour() const { return h; };
        void set_hour(int new_hour) { h = new_hour; };
        int get_min() const { return min; };
        void set_min(int new_min) { min = new_min; };

    private:
        int h;
        int min;
    };

    std::ostream& operator << (std::ostream& os, const Time& t);
    std::istream& operator >> (std::istream& in, Time& t);
    
// Month
    enum class Month
    {
        jan = 1, feb, mar, apr, may, jun,
        jul, aug, sep, oct, nov, dec
    };

    Month operator ++ (Month& m);
    Month operator -- (Month& m);
    Month conversion(std::string month_name);
    std::string month_to_string(Month month); 

    class Period;

// Date
    class Date
    {
    public:
        Date(int d, Month m, int y);
        Date(): d{0}, m{Month::jan}, y{0} {}

        int day() const { return d; }
        Month month() const { return m; }
        int year() const { return y; }
        bool in_period(Period p);

    protected:
        int d;
        Month m;
        int y;
    };

    bool is_date(int d, Month m, int y); // true для корректной даты
    bool leapyear(unsigned y);
    Date operator ++ (Date& d);
    bool operator == (const Date& d1, const Date& d2);
    bool operator != (const Date& d1, const Date& d2);
    bool operator < (const Date& d1, const Date& d2);
    bool operator <= (const Date& d1, const Date& d2);
    bool operator > (const Date& d1, const Date& d2);
    bool operator >= (const Date& d1, const Date& d2);
    std::ostream& operator << (std::ostream& os, const Date& d);
    //std::istream& operator >> (std::istream& is, Date& dd);
    //Date operator - (const Date& d); // ЭТО ДЕЛАТЬ В ПОСЛЕДНЮЮ ОЧЕРЕДЬБ ВЕДЬ В ctime может быть функция, возвращающая текущую неделю.
   
// Period
    class Period
    {
    public:
        Period(Time start_time, Date start_date, Time end_time, Date end_date);
        Period(): start_t{0,0}, end_t{0,0}, start_d{}, end_d{} {} // попробовать создавать дефолтную дату здесь, 
                                                                  // а в Date удалить дефолтный конструктор
        int start_hour() const { return start_t.get_hour(); }
        int start_min() const { return start_t.get_min(); }
        int end_hour() const { return end_t.get_hour(); }
        int end_min() const { return end_t.get_min(); }
        Date start_date() const { return start_d; }
        Date end_date() const { return end_d; }

    private:
        Time start_t; 
        Time end_t;
        Date start_d;
        Date end_d;
    };

    bool is_period(Time start_t, Date start_date, Time end_t, Date end_date);
    bool operator == (const Period& t1, const Period& t2);
    bool operator != (const Period& t1, const Period& t2);
    bool operator < (const Period& p1, const Period& p2);
    std::ostream& operator << (std::ostream& os, const Period& t);

// Other
    int days_in_month(Month month, int year);
    std::vector<Date> get_week_dates();
    Date today();
    Date monday_date();

}


#endif //CHRONO