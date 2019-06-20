#ifndef COLUMNS_H
#define COLUMNS_H

#include <string>
#include <memory>
#include <vector>
#include "datadefinition.h"
#include "charmap.h"
#include "datetime.h"

class Columns;

typedef std::unique_ptr<Columns> up_columns;
typedef std::unique_ptr<std::vector<up_columns>> up_vecols;

typedef CharMap<int> mapInt;
typedef CharMap<std::string> mapStr;
typedef CharMap<double> mapFloat;
typedef CharMap<bool> mapBool;
typedef CharMap<Datetime> mapDt;

/**
 * This is a class that holds data for one row or one
 * object at a time. It can hold data for only int,
 *std::string, bool, double. But can be easily extended for
 * more data types limited only by the ones supported
 * by sqlite3. The specialized templated functions help
 * seemlessly add values to the internal associative
 * containers.
*/
class Columns
{
  private:
    mapInt m_intColumns;
    mapStr m_strColumns;
    mapBool m_boolColumns;
    mapDt m_dtColumns;
    mapFloat m_dblColumns;

    template <typename T>
    void inline swap(const CharMap<T> &sourceColumn, CharMap<T> &destColumn) const
    {
        destColumn.clear();
        for (const auto &elem : sourceColumn)
        {
            destColumn.insert(elem);
        }
    }

    template <typename T>
    void inline set(const char *key, const T &value, CharMap<T> &column) const
    {
        if (column.find(key) != column.end())
        {
            column[key] = value;
        }
        else
        {
            column.insert(std::make_pair(key, value));
        }
    }
    template <typename T>
    bool inline get(T &refVar, const char *key, CharMap<T> &column) const
    {
        if (column.find(key) == column.end())
        {
            return false;
        }
        refVar = column[key];
        return true;
    }

  protected:
    void set(const char *key, const int &value);
    void set(const char *key, const unsigned int &value);
    void set(const char *key, const float &value);
    void set(const char *key, const double &value);
    void set(const char *key, const std::string &value);
    void set(const char *key, const char *value);
    void set(const char *key, const bool &value);
    void set(const char *key, const Datetime &value);

  public:
    virtual schema getSchema() const
    {
        schema scma;
        auto add = [&scma](const char *name, PlatformTypeEnum tp) { scma.insert(std::make_pair(name, tp)); };

        for (const std::pair<const char *, bool> &p : m_boolColumns)
            add(p.first, PLAT_BOOL);
        for (const std::pair<const char *, Datetime> &p : m_dtColumns)
            add(p.first, PLAT_DT);
        for (const std::pair<const char *, double> &p : m_dblColumns)
            add(p.first, PLAT_DBL);
        for (const std::pair<const char *, int> &p : m_intColumns)
            add(p.first, PLAT_INT);
        for (const std::pair<const char *, std::string> &p : m_strColumns)
            add(p.first, PLAT_STR);
        return scma;
    }

    // bool hasValue(const char *key, const PlatformTypeEnum &type);
    // bool hasValue(const char *key);

    int getInt(const char *key, const int &def = 0);
    char *getChar(const char *key, const char *def = 0);
    unsigned int getUInt(const char *key, const unsigned int &def = 0);
    double getDouble(const char *key, const double &def = 0.0);
    float getFloat(const char *key, const float &def = 0.0);
    std::string getString(const char *key, const std::string &def = "");
    int getBool(const char *key, const int &def = -1);
    Datetime getDt(const char *key, const int &def = 0);

    bool get(int &refVar, const char *key);
    bool get(unsigned int &refVar, const char *key);
    bool get(float &refVar, const char *key);
    bool get(double &refVar, const char *key);
    bool get(std::string &refVar, const char *key);
    bool get(const char *refVar, const char *key);
    bool get(bool &refVar, const char *key);
    bool get(Datetime &refVar, const char *key);

    void clear()
    {
        m_intColumns.clear();
        m_strColumns.clear();
        m_boolColumns.clear();
        m_dtColumns.clear();
        m_dblColumns.clear();
    }
    void swap(const Columns &cols);
};
class ColumnsItem : public Columns
{
  public:
    // PLAT_STR
    void Set(const char *key, const std::string &value)
    {
        set(key, value);
    }

    // PLAT_DBL
    void Set(const char *key, const double &value)
    {
        set(key, value);
    }

    // PLAT_INT
    void Set(const char *key, const int &value)
    {
        set(key, value);
    }

    // PLAT_BOOL
    void Set(const char *key, const bool &value)
    {
        set(key, value);
    }

    // PLAT_DT
    void Set(const char *key, const Datetime &value)
    {
        set(key, value);
    }
};

#endif //COLUMNS_HColumns
