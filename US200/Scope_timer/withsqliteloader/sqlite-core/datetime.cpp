#include "datetime.h"

Datetime::Datetime(tm *lclTm, const bool &isTimeOnly) : m_lclTm{lclTm}, m_isTimeOnly{isTimeOnly} {}
Datetime::Datetime(const time_t &t) : Datetime(localtime(&t), false) {}
Datetime::Datetime(int year, int month, int date) : Datetime(broken(year, month, date)) {}
Datetime::Datetime(int year, int month, int date, int hour, int min, int sec) : Datetime(broken(year, month, date, hour, min, sec)) {}

std::string Datetime::toString(const DatetimeFormatEnum &format) const
{
    char buffer[80];
    switch (format)
    {
    case DatetimeFormatEnum::YYYY_MM_DD_HH_MM:
    {
        size_t sz = strftime(buffer, 80, "%Y-%m-%d %H:%M", m_lclTm);
        return std::string(buffer, sz);
    }
    case DatetimeFormatEnum::HH_MM_SS:
    {
        size_t sz = strftime(buffer, 80, "%X", m_lclTm);
        return std::string(buffer, sz);
    }
    case DatetimeFormatEnum::MM_DD_YYYY:
    {
        size_t sz = strftime(buffer, 80, "%x", m_lclTm);
        return std::string(buffer, sz);
    }
    case DatetimeFormatEnum::DEFAULT:
    {
        if (m_isTimeOnly)
        {
            size_t sz = strftime(buffer, 80, "%X", m_lclTm);
            return std::string(buffer, sz);
        }
        else
        {
            size_t sz = strftime(buffer, 80, "%c", m_lclTm);
            return std::string(buffer, sz);
        }
    }
    }
    return NULL;
}

time_t Datetime::toNative() const
{
    return mktime(m_lclTm);
}
