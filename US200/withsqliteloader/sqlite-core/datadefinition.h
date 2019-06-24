#ifndef DATADEFINITION_H
#define DATADEFINITION_H

#include "charmap.h"
#include "datetime.h"
#include "stringutils.h"

using namespace StringUtils;

#define NULVAL nullptr
enum PlatformTypeEnum
{
    PLAT_STR,
    PLAT_INT,
    PLAT_DBL,
    PLAT_BOOL,
    PLAT_DT
};

enum SqlTypeEnum
{
    SQL_STR,
    SQL_INT,
    SQL_DBL,
    SQL_NUL,
    LOGC
};

enum FilterOperatorEnum
{
    EQ,
    LT,
    LTQ,
    GT,
    GTQ,
    NQ
};

struct PlatUnit
{

    const char *Name;
    int IntVal = 0;
    std::string TxtVal = "";
    double DblVal = 0;
    bool BoolVal = false;
    Datetime DtVal;
    PlatformTypeEnum Tp;
    PlatUnit() = default;

    PlatUnit(const char *name, const int &intVal) : Name(name), IntVal(intVal), Tp(PLAT_INT) {}
    PlatUnit(const char *name, const std::string &charVal) : Name(name), TxtVal(charVal), Tp(PLAT_STR) {}
    PlatUnit(const char *name, const double &dblVal) : Name(name), DblVal(dblVal), Tp(PLAT_DBL) {}
    PlatUnit(const char *name, const bool &boolVal) : Name(name), BoolVal(boolVal), Tp(PLAT_BOOL) {}
    PlatUnit(const char *name, const Datetime &dtVal) : Name(name), DtVal(dtVal), Tp(PLAT_DT) {}
};

template <typename T>
std::string to_string(T value)
{
    std::string os;
    os << value;
    return os;
}

/**
 * This stucture holds value of one column coming
 * from the sqlite3 db. They can be any type. While
 * initializing the object, it is determined as to
 * what data type the column is initialized as.
 * This struct can be improved in many ways. To
 * begin with, it could be converted into a union.
*/
struct SqlUnit
{
    const char *Name;
    int IntVal = 0;
    std::string TxtVal = "";
    double FltVal = 0;
    SqlTypeEnum Tp;
    bool IsNull = false;
    SqlUnit() = default;
    SqlUnit(const char *name, const int &intVal) : Name(name), IntVal(intVal), Tp(SQL_INT) {}
    SqlUnit(const char *name, const std::string &charVal) : Name(name), TxtVal(charVal), Tp(SQL_STR) {}
    SqlUnit(const char *name, const double &dblVal) : Name(name), FltVal(dblVal), Tp(SQL_DBL) {}
    SqlUnit(const char *name, const SqlTypeEnum &tp) : Name(name), Tp(tp), IsNull{true} {}
    SqlUnit(const char *name) : Name(name), Tp(SQL_NUL), IsNull{true} {}
    


    std::string toString() const
    {
        switch (Tp)
        {
        case SQL_DBL:
            return IsNull ? "NULL" : to_string(FltVal);
        case SQL_INT:
            return IsNull ? "NULL" : to_string(IntVal);
        case SQL_STR:
            return IsNull ? "NULL" : TxtVal;
        default:
            return "NULL";
        }
    }
};

struct DBField
{
    DBField(
            const char *name,
            const SqlTypeEnum &type = SqlTypeEnum::SQL_STR,
            const bool &isKey = false,
            const int &sz = 0,
            const bool &notNull = false) : Name(name), Type(type), Sz(sz), IsKey(isKey), NotNull(notNull) {}
    const char *Name;
    SqlTypeEnum Type;
    int Sz;
    bool IsKey;
    bool NotNull;
};


typedef CharMap<SqlUnit> mapSqlUnit;
typedef CharMap<PlatformTypeEnum> schema;

#endif //DATADEFINITION_H
