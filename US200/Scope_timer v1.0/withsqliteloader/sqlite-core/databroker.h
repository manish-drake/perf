#ifndef DATABROKER_H
#define DATABROKER_H

#include <vector>
#include <utility>
#include "table.h"
#include "columns.h"
#include "datetime.h"

namespace ColumnsCollection
{
inline mapSqlUnit mapFromVec(const std::vector<SqlUnit> &values)
{
    mapSqlUnit valueMap;
    for (const SqlUnit &val : values)
    {
        valueMap.insert(std::make_pair(val.Name, val));
    }
    return valueMap;
}

template <typename TO, typename FROM>
inline std::unique_ptr<TO> static_unique_pointer_cast(std::unique_ptr<FROM> &&up)
{
    return std::unique_ptr<TO>(static_cast<TO *>(up.release()));
}

inline up_columns create(const schema &schm, const std::vector<SqlUnit> &values)
{
    std::unique_ptr<ColumnsItem> cols(new ColumnsItem);
    mapSqlUnit valueMap = mapFromVec(values);

    cols->Set("_ID", valueMap["_ID"].IntVal);

    for (const std::pair<const char *, PlatformTypeEnum> &pair : schm)
    {
        const char *name = pair.first;
        if (valueMap[name].IsNull) //NULL values need to be simply ignored
            continue;

        switch (pair.second)
        {
        case PLAT_STR:
            cols->Set(name, valueMap[name].TxtVal);
            break;
        case PLAT_DBL:
            cols->Set(name, valueMap[name].FltVal);
            break;
        case PLAT_INT:
            cols->Set(name, valueMap[name].IntVal);
            break;
        case PLAT_BOOL:
            cols->Set(name, (bool)valueMap[name].IntVal);
            break;
        case PLAT_DT:
            cols->Set(name, Datetime((time_t)valueMap[name].IntVal));
            break;
        default:
            break;
        }
    }
    return static_unique_pointer_cast<Columns>(std::move(cols));
}
} // namespace ColumnsCollection

namespace SqlUnitCollection
{
inline int create(Columns &cols, const schema &schm, std::vector<SqlUnit> &sqlUnits)
{
    int count = 0;
    for (const std::pair<const char *, PlatformTypeEnum> pair : schm)
    {
        const char *name = pair.first;
        switch (pair.second)
        {
        case PLAT_STR:
        {
           std::string val = "";
            if (cols.get(val, name))
                sqlUnits.push_back(SqlUnit(name, val));
            else
                sqlUnits.push_back(SqlUnit(name, SQL_NUL));
            break;
        }
        case PLAT_DBL:
        {
            double val = 0.0;
            if (cols.get(val, name))
                sqlUnits.push_back(SqlUnit(name, val));
            else
                sqlUnits.push_back(SqlUnit(name, SQL_NUL));
            break;
        }
        case PLAT_BOOL:
        {
            bool val = false;
            if (cols.get(val, name))
                sqlUnits.push_back(SqlUnit(name, val));
            else
                sqlUnits.push_back(SqlUnit(name, SQL_NUL));
            break;
        }
        case PLAT_DT:
        {
            Datetime val;
            if (cols.get(val, name))
                sqlUnits.push_back(SqlUnit(name, (int)val.toNative()));
            else
                sqlUnits.push_back(SqlUnit(name, SQL_NUL));
            break;
        }
        case PLAT_INT:
        {
            int val = 0;
            if (cols.get(val, name))
                sqlUnits.push_back(SqlUnit(name, val));
            else
                sqlUnits.push_back(SqlUnit(name, SQL_NUL));
            break;
        }
        default:
            break;
        }
        count++;
    }
    return count;
}
} // namespace SqlUnitCollection
namespace DBFieldCollection
{
inline int create(const schema &schm,std::vector<DBField> &fields)
{
    int count = 0;
    for (const std::pair<const char *, PlatformTypeEnum> &pair : schm)
    {
        switch (pair.second)
        {
        case PLAT_BOOL:
            fields.push_back(DBField(pair.first, SQL_INT));
            break;
        case PLAT_DT:
            fields.push_back(DBField(pair.first, SQL_INT));
            break;
        case PLAT_DBL:
            fields.push_back(DBField(pair.first, SQL_DBL));
            break;
        case PLAT_INT:
            fields.push_back(DBField(pair.first, SQL_INT));
            break;
        case PLAT_STR:
            fields.push_back(DBField(pair.first, SQL_STR));
            break;
        }
        count++;
    }
    return count;
}
inline int create(const std::vector<SqlUnit> &sqlUnits,std::vector<DBField> &fields)
{
    int count = 0;
    for (const SqlUnit &val : sqlUnits)
    {
        fields.push_back(DBField(val.Name, val.Tp));
        count++;
    }
    return count;
}
} // namespace DBFieldCollection

#endif //DATABROKER_H
