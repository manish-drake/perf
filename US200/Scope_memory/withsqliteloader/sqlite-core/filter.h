#ifndef FILTER_H
#define FILTER_H

#include <vector>
#include <string>
#include "datadefinition.h"

struct UnitFilter
{
    const char *Key;
    FilterOperatorEnum FOp;
    std::string Value;
    SqlTypeEnum Tp;
    UnitFilter(const char *logicalOperator) : Key{logicalOperator},
                                              FOp{EQ},
                                              Value{""},
                                              Tp{LOGC}
    {
    }

    UnitFilter(const char *key, const FilterOperatorEnum &fOp, const std::string &value, const SqlTypeEnum &tp) : Key{key},
                                                                                                             FOp{fOp},
                                                                                                             Value{value},
                                                                                                             Tp{tp}
    {
    }
};

class Filter
{
  public:
    static std::string getOpStr(const FilterOperatorEnum &fOp)
    {
        switch (fOp)
        {
        case LT:
            return " < ";
        case LTQ:
            return " <= ";
        case GT:
            return " > ";
        case GTQ:
            return " >= ";
        case NQ:
            return " < ";
        case EQ:
        default:
            return " == ";
        }
    }

    Filter()
    {
    }
    Filter(const char *key, const int &value, const FilterOperatorEnum &fOp = EQ)
    {
        apply_filter(key, value, fOp);
    }
    Filter(const char *key, const double &value, const FilterOperatorEnum &fOp = EQ)
    {
        apply_filter(key, value, fOp);
    }
    Filter(const char *key, const std::string &value, const FilterOperatorEnum &fOp = EQ)
    {
        apply_filter(key, value, fOp);
    }
    Filter(const char *key, const bool &value, const FilterOperatorEnum &fOp = EQ)
    {
        apply_filter(key, value, fOp);
    }

    Filter &apply_filter(const char *key, const int &value, const FilterOperatorEnum &fOp = EQ)
    {
        m_filters.push_back(UnitFilter(key, fOp, to_string(value), SQL_INT));
        return *this;
    }
    Filter &apply_filter(const char *key, const double &value, const FilterOperatorEnum &fOp = EQ)
    {
        m_filters.push_back(UnitFilter(key, fOp, to_string(value), SQL_DBL));
        return *this;
    }
    Filter &apply_filter(const char *key, const std::string &value, const FilterOperatorEnum &fOp = EQ)
    {
        m_filters.push_back(UnitFilter(key, fOp, value, SQL_STR));
        return *this;
    }
    Filter &apply_filter(const char *key, const char* value, const FilterOperatorEnum &fOp = EQ)
    {
        m_filters.push_back(UnitFilter(key, fOp,std::string(value), SQL_STR));
        return *this;
    }
    Filter &apply_filter(const char *key, const bool &value, const FilterOperatorEnum &fOp = EQ)
    {
        m_filters.push_back(UnitFilter(key, fOp, to_string(value), SQL_INT));
        return *this;
    }

    Filter &AND()
    {
        m_filters.push_back("AND");
        return *this;
    }

    Filter &OR()
    {
        m_filters.push_back("OR");
        return *this;
    }

    Filter &NOT()
    {
        m_filters.push_back("NOT");
        return *this;
    }

   std::vector<UnitFilter> get() const
    {
        return m_filters;
    }

  private:
   std::vector<UnitFilter> m_filters;
};

inline Filter apply_filter(const char *key, const int &value, const FilterOperatorEnum &fOp = EQ)
{
    return Filter(key, value, fOp);
}
inline Filter apply_filter(const char *key, const double &value, const FilterOperatorEnum &fOp = EQ)
{
    return Filter(key, value, fOp);
}
inline Filter apply_filter(const char *key, const std::string &value, const FilterOperatorEnum &fOp = EQ)
{
    return Filter(key, value, fOp);
}

inline Filter apply_filter(const char *key, const char* value, const FilterOperatorEnum &fOp = EQ)
{
    return Filter(key,std::string(value), fOp);
}
inline Filter apply_filter(const char *key, const bool &value, const FilterOperatorEnum &fOp = EQ)
{
    return Filter(key, value, fOp);
}

#endif //FILTER_H
