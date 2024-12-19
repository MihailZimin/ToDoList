#ifndef CHRONO
#define CHRONO

#include <string>
#include <vector>

namespace Chrono_ns
{
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
    Date today();
    Date monday_date();


    class Period
    {
    public:
        Period(int start_hour, int start_min, Date start_date, int end_hour, int end_min, Date end_date);
        Period(): start_h{0}, start_m{0}, end_h{0}, end_m{0}, start_d{}, end_d{} {}

        int start_hour() const { return start_h; }
        int start_min() const { return start_m; }
        int end_hour() const { return end_h; }
        int end_min() const { return end_m; }
        Date start_date() const { return start_d; }
        Date end_date() const { return end_d; }

    private:
        int start_h;
        int start_m;
        int end_h;
        int end_m;
        Date start_d;
        Date end_d;
    };

    bool is_period(int start_hour, int start_min, Date start_date, 
                   int end_hour, int end_min, Date end_date);
    bool operator == (const Period& t1, const Period& t2);
    bool operator != (const Period& t1, const Period& t2);
    bool operator < (const Period& p1, const Period& p2);
    std::ostream& operator << (std::ostream& os, const Period& t);

    int days_in_month(Month month, int year);
    std::vector<Date> get_week_dates();
}


#endif //CHRONO