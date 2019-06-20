#ifndef DATETIME_H
#define DATETIME_H
#include <ctime>
#include <memory>
#include <string>

enum DatetimeFormatEnum
{
    DEFAULT,
    YYYY_MM_DD_HH_MM,
    MM_DD_YYYY,
    HH_MM_SS
};

class Datetime
{
    tm *m_lclTm;
    Datetime(tm *lclTm, const bool &isTimeOnly);
    static time_t broken(int year, int month, int date, int hour = 0, int min = 0, int sec = 0)
    {
        struct tm t = {sec, min, hour, date, month - 1, year - 1900, 0, 0, 0, 0, 0};
        return mktime(&t);
    }

    bool m_isTimeOnly;
  public:
    static Datetime Current()
    {
        time_t t = time(0);
        tm *lclTm = localtime(&t);
        return Datetime(lclTm, false);
    }
    static std::unique_ptr<Datetime> Current_UP()
    {
        time_t t = time(0);
        tm *lclTm = localtime(&t);
        return std::unique_ptr<Datetime>(new Datetime(lclTm, false));
    }
    static Datetime Timespan(int hour, int min, int sec)
    {
        time_t timespan = broken(0, 0, 0, hour, min, sec);
        return Datetime(localtime(&timespan), true);
    }

    Datetime() = default;
    Datetime(const time_t &t);
    Datetime(int year, int month, int date);
    Datetime(int year, int month, int date, int hour, int min, int sec);
    
    
    std::string toString(const DatetimeFormatEnum &format = DatetimeFormatEnum::DEFAULT) const;
    time_t toNative() const;

    inline bool Equals(const Datetime &match) const
    {
        return this->toNative() == match.toNative();
    }
};



#endif //DATETIME_H
