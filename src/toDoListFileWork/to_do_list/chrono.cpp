#include "chrono.h"
#include <stdexcept>
#include <iostream>

#include <vector>

#include <chrono>
#include <ctime> 

namespace Chrono_ns
{
    Month operator ++ (Month& m)
    {
        m = (m == Month::dec) ? Month::jan : Month(int(m) + 1);
        return m;
    }

    Month operator -- (Month& m)
    {
        m = (m == Month::jan) ? Month::dec : Month(int(m) - 1);
        return m;
    }


    Date::Date(double dd, Month mm, double yy)
        : d{unsigned(dd)}, m{mm}, y{int(yy)}
    {
        if(!is_date(dd, mm, yy))
            throw std::runtime_error("Uncorrect date"/* + dd + '.' + int(mm) + '.' + yy*/); 
    }

    bool leapyear(unsigned y) //ПЕРЕПИСАТЬ
    {
        return false;
    }

    bool is_date(double d, Month m, double y)
    {
        if(d <= 0 || (d - int(d)) != 0 || (y - int(y)) != 0)
            return false;

        if(m < Month::jan || Month::dec < m)
            return false;

        int days_in_month = 31;

        switch(m)
        {
        case Month::feb:
            days_in_month = leapyear(y) ? 29 : 28;
            break;
        case Month::apr:
        case Month::jun:
        case Month::sep:
        case Month::nov:
            days_in_month = 30;
            break;
        }
        if(d > days_in_month)
            return false;

        return true;
    }

    bool Date::in_period(Period p) { return (p.start_date() <= *this && p.end_date() >= *this); }

    bool operator == (const Date& d1, const Date& d2)
    {
        return d1.day() == d2.day()
            && d1.month() == d2.month()
            && d1.year() == d2.year();
    }

    bool operator != (const Date& d1, const Date& d2)
    {
        return !(d1 == d2);
    }

    bool operator < (const Date& d1, const Date& d2)
    {
        if (d1.year() > d2.year())
            return false;
        else 
        {
            if(d1.year() == d2.year() && d1.month() > d2.month())
                return false;
            else
            {
                if(d1.year() == d2.year() && d1.month() == d2.month() && d1.day() >= d2.day())
                    return false;
            }
        }
        return true;
    }

    bool operator <= (const Date& d1, const Date& d2)
    {
        return d1 < d2 || d1 == d2;
    }

    bool operator > (const Date& d1, const Date& d2)
    {
        return !(d1 <= d2);
    }

    bool operator >= (const Date& d1, const Date& d2)
    {
        return !(d1 < d2);
    }

    std::ostream& operator << (std::ostream& os, const Date& d)
    {
        return os << d.day()
                  << '.' << int(d.month())
                  << '.' << d.year();
    }


    Period::Period(unsigned start_hour, unsigned start_min, Date start_date, unsigned end_hour, unsigned end_min, Date end_date)
        :start_h {start_hour}, start_m {start_min}, end_h {end_hour}, end_m {end_min}, start_d {start_date}, end_d {end_date}
    {
        if(!is_period(start_hour, start_min, start_date, end_hour, end_min, end_date))
            throw std::runtime_error("Uncorrect period value"); 
    }

    bool is_period(unsigned start_hour, unsigned start_min, Date start_date, unsigned end_hour, unsigned end_min, Date end_date)
    {
        if((end_hour == start_hour && end_min <= start_min || end_hour < start_hour) && end_date == start_date
                                                                                     || end_date < start_date)
            return false;
        return true;
    }

    bool operator == (const Period& t1, const Period& t2)
    {
        return t1.start_hour() == t2.start_hour()
            && t1.start_min() == t2.start_min()
            && t1.end_hour() == t2.end_hour()
            && t1.end_min() == t2.end_min()
            && t1.start_date() == t2.start_date()
            && t1.end_date() == t2.end_date();
    }

    bool operator != (const Period& t1, const Period& t2)
    {
        return !(t1 == t2);
    }

    std::ostream& operator << (std::ostream& os, const Period& t)
    {
        return os << '(' << t.start_hour()
                  << ':' << t.start_min()
                  << "  "<< t.start_date()
                  << " - " << t.end_hour()
                  << ':' << t.end_min()
                  << "  "<< t.end_date()
                  << ')';
    }


    unsigned days_in_month(Month month, float year)
    {
        if(year - int(year) != 0)
            throw std::runtime_error("Year must have integer type");

        unsigned days_in_month = 31;

        switch(month)
        {
        case Month::feb:
            days_in_month = leapyear(year) ? 29 : 28;
            break;
        case Month::apr:
        case Month::jun:
        case Month::sep:
        case Month::nov:
            days_in_month = 30;
            break;
        }
        return days_in_month;
    }


    Date today()
    {
        time_t mytime = time(NULL);
        struct tm *now = localtime(&mytime);
        return Date(now->tm_mday,static_cast<Month>(1 + now->tm_mon), 1900 + now->tm_year);
    }

    Date monday_date()
    {
        time_t mytime = time(NULL);
        struct tm *now = localtime(&mytime);
        Date today = Chrono_ns::today();
        unsigned days_after_sunday = now->tm_wday;
        unsigned days_after_monday = days_after_sunday == 0 ? 6 : days_after_sunday - 1;

        int monday_day = today.day() - days_after_monday;
        Month monday_month = today.month();
        unsigned monday_year = today.year();
        if(monday_day < 1)
        {
            --monday_month;
            int to_minus_from_prev_month = -monday_day;
            unsigned days_in_prev_month = Chrono_ns::days_in_month(monday_month, today.year());
            monday_day = days_in_prev_month - to_minus_from_prev_month;
            if(monday_month == Month::dec)
                --monday_year;
        }
        return Date(monday_day, monday_month, monday_year);
    }
}