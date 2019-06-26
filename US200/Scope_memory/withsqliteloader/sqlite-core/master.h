#ifndef MASTER_H
#define MASTER_H

#include <string>
#include <vector>
#include "datadefinition.h"
#include "catalogue.h"
#include "datetime.h"

class Master
{
    struct TVal
    {
        const char *key;
        bool m_bool;
        Datetime m_dt;
        int m_int;
        double m_double;
       std::string m_string;
        bool m_isNull = false;
        TVal(std::nullptr_t &val) : m_isNull{true} {std::ignore = val;} // unused parameter 'val'
        TVal(const bool &val) : m_bool{val} {}
        TVal(const Datetime &val) : m_dt{val} {}
        TVal(const int &val) : m_int{val} {}
        TVal(const double &val) : m_double{val} {}
        TVal(const std::string &val) : m_string{val} {}
        TVal(const char *val) : m_string{val} {}
    };
    std::vector<std::vector<TVal>> m_rows;
    std::vector<TVal> m_row;
    const char *m_table;
    const schema m_schema;
    int m_argIndex = 0;

    void addToList(std::vector<TVal> &list, const schema &schm, const int &schmIndex, std::nullptr_t value)
    {
        list.push_back(value);
         std::ignore = schm;              // UNUSED parameter 'schm'
         std::ignore = schmIndex;         // UNUSED parameter 'schmIndex'
    }
    void addToList(std::vector<TVal> &list, const schema &schm, const int &schmIndex, const Datetime &value)
    {
        list.push_back(value);
        std::ignore = schm;              // UNUSED parameter 'schm'
        std::ignore = schmIndex;         // UNUSED parameter 'schmIndex'
    }

    void addToList(std::vector<TVal> &list, const schema &schm, const int &schmIndex, const std::string &value)
    {
        list.push_back(value);
        std::ignore = schm;              // UNUSED parameter 'schm'
        std::ignore = schmIndex;         // UNUSED parameter 'schmIndex'
    }
    void addToList(std::vector<TVal> &list, const schema &schm, const int &schmIndex, const char* value)
    {
        list.push_back(value);
        std::ignore = schm;              // UNUSED parameter 'schm'
        std::ignore = schmIndex;         // UNUSED parameter 'schmIndex'
    }
    template <typename T>
    void addToList(std::vector<TVal> &list, const schema &schm, const int &schmIndex, T value)
    {
        auto pair = schm.begin();
        std::advance(pair, schmIndex);
        switch (pair->second)
        {
        case PLAT_STR:
            list.push_back(to_string(value));
            break;
        case PLAT_DBL:
            list.push_back((double)value);
            break;
        case PLAT_INT:
            list.push_back((int)value);
            break;
        case PLAT_BOOL:
            list.push_back((bool)value);
            break;
        case PLAT_DT:
            list.push_back((Datetime)value);
        default:
            break;
        }
    }

  public:
    Master(const char *table, const schema &sch);
    inline const char *Table() const
    {
        return m_table;
    }
    inline const schema &Schema() const
    {
        return m_schema;
    }
    template <class T>
    Master &Add(T arg)
    {

        addToList(m_row, m_schema, m_argIndex, arg);
        m_rows.push_back(m_row);
        m_argIndex = 0;
        m_row.clear();
        return *this;
    }

    template <class T, class... R>
    Master &Add(T arg, R... rest)
    {
        addToList(m_row, m_schema, m_argIndex, arg);
        m_argIndex += 1;
        Add(rest...);
        return *this;
    }
    Master &Save(const char *db);
};

#endif //MASTER_H
