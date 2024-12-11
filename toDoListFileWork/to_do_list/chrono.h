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

    class Period;

    class Date
    {
    public:
        Date(unsigned d, Month m, unsigned y);
        Date() = delete;

        unsigned day() const { return d; }
        Month month() const { return m; }
        unsigned year() const { return y; }
        bool in_period(Period p);

    protected:
        unsigned d;
        Month m;
        unsigned y;
    };

    bool is_date(unsigned d, Month m, unsigned y);
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
        Period(unsigned start_hour, unsigned start_min, Date start_date, unsigned end_hour, unsigned end_min, Date end_date);
        Period() = delete;

        unsigned start_hour() const { return start_h; }
        unsigned start_min() const { return start_m; }
        unsigned end_hour() const { return end_h; }
        unsigned end_min() const { return end_m; }
        Date start_date() const { return start_d; }
        Date end_date() const { return end_d; }

    private:
        unsigned start_h;
        unsigned start_m;
        unsigned end_h;
        unsigned end_m;
        Date start_d;
        Date end_d;
    };

    bool is_period(unsigned start_hour, unsigned start_min, Date start_date, 
                   unsigned end_hour, unsigned end_min, Date end_date);
    bool operator == (const Period& t1, const Period& t2);
    bool operator != (const Period& t1, const Period& t2);
    std::ostream& operator << (std::ostream& os, const Period& t);

    unsigned days_in_month(Month month, unsigned year);
    std::vector<Date> get_week_dates();
}


#endif //CHRONO