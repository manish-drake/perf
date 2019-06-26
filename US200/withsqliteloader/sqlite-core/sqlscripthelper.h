#ifndef SQLFACTORY_H
#define SQLFACTORY_H

#include <string>
#include <cstdio>
#include <utility>
#include <vector>
#include "datadefinition.h"
#include "filter.h"
#include "stringutils.h"

using namespace StringUtils;
/**
 * This is the class where all sqlstd::strings are made
 * out of the data that it receives from client objects.
 * It has functions for INSERT, SELECT and CREATE TABLE.
 * More can be added in due course.
*/
class SqlScriptHelper
{
  private:
    static inline void join(const std::vector<std::string> &v, char c,std::string &s)
    {
        s.clear();
        for (std::vector<std::string>::const_iterator p = v.begin();
             p != v.end(); ++p)
        {
            s += *p;
            if (p != v.end() - 1)
            {
                s += c;
            }
        }
    }
    static const char *SqlTypeEnum_To_Str(SqlTypeEnum type)
    {
        switch (type)
        {
        // case CHAR:
        //     return "CHAR";
        // case NUMERIC:
        // return "NUMERIC";
        case SQL_INT:
            return "INTEGER";
        case SQL_DBL:
            return "REAL";
        // case BLOB:
        //     return "BLOB";
        case SQL_STR:
        default:
            return "TEXT";
        }
    }

    static std::string fieldSpecs(SqlTypeEnum type, int sz = 0, bool isKey = false, bool notNull = false)
    {
       std::string ss;
        char szSpec[10];
        char keySpec[12];
        char nullSpec[10];

        if (sz > 0)
        {
            sprintf(szSpec, " (%i)", sz);
        }
        else
        {
            sprintf(szSpec, " ");
        }

        if (isKey)
        {
            sprintf(keySpec, " PRIMARY KEY");
        }
        else
        {
            sprintf(keySpec, " ");
        }

        if (notNull)
        {
            sprintf(nullSpec, " NOT NULL");
        }
        else
        {
            sprintf(nullSpec, " ");
        }

        ss
            << SqlTypeEnum_To_Str(type)
            << szSpec
            << keySpec
            << nullSpec;
        return ss;
    }

    static std::string ddlCat(const DBField& field)
    {
       std::string ss;
        ss << field.Name << " " << fieldSpecs(field.Type, field.Sz, field.IsKey, field.NotNull);
        return ss;
    }

    static void dmlCat(
       std::string &partSql,
       std::vector<std::string>::iterator itrName,
       std::vector<std::string>::iterator itrValue,
        const std::vector<std::string> &names,
        const std::vector<std::string> &values)
    {
       std::string os;
        os
            << *itrName
            << " = "
            << *itrValue;
        partSql += os;

        ++itrName;
        ++itrValue;
        if (itrName != names.end())
        {
            partSql += ", ";
            dmlCat(partSql, itrName, itrValue, names, values);
        }
    }

    static std::string WHERE(const Filter &filters)
    {
       std::string clause;
        for (const UnitFilter &filter : filters.get())
        {
            clause << ((clause.length() <= 0) ? "WHERE " : " ");

            if (filter.Tp == LOGC)
            {
                clause << " " << filter.Key << " ";
            }
            else
            {
                clause
                    << filter.Key
                    << Filter::getOpStr(filter.FOp)
                    << treatSqlUnit(filter.Value, filter.Tp);
            }
        }

        return clause;
    }

  public:
    static std::string treatSqlUnit(const std::string &value, const SqlTypeEnum &type)
    {
        switch (type)
        {
        case SQL_DBL:
        case SQL_INT:
        {
           std::string os;
            os << value;
            return os;
        }
        case SQL_NUL:
        {
           std::string os;
            os << "NULL";
            return os;
        }
        case SQL_STR:
        default:
        {
           std::string os;
            os << "'" << value << "'";
            return os;
        }
        }
    }

    static std::string TABLE_EXISTS(const char *tablename)
    {
       std::string os;
        os
            << "SELECT name FROM sqlite_master WHERE type='table' and name="
            << "'"
            << tablename
            << "'";
        return os;
    }

    static std::string CREATE_TABLE(const char *tableName, const std::vector<DBField> &dbFields)
    {
       std::string os;
        std::string fieldsList;

        for (const DBField &sqlf : dbFields)
        {
            fieldsList += ((fieldsList.length() > 0) ? "," : "") +
                          ddlCat(sqlf);
        }

        os
            << "CREATE TABLE "
            << tableName
            << "( "
            << fieldsList
            << ");";
        return os;
    }

    static std::string DROP_TABLE(const char *tableName)
    {
       std::string os;
        os
            << "DROP TABLE IF EXISTS "
            << tableName
            << ";";
        return os;
    }

    static std::string INSERT_TABLE(const char *tableName, std::string names, std::string values)
    {
       std::string ss;
        ss
            << "INSERT INTO "
            << tableName
            << " ("
            << names
            << ") "
            << "VALUES("
            << values
            << ")";

        return ss;
    }

    static std::string INSERT_TABLE(
        const char *tableName,
       std::vector<std::string> names,
       std::vector<std::string> values)
    {
       std::string strNames, strValues;
        join(names, ',', strNames);
        join(values, ',', strValues);
        return INSERT_TABLE(tableName, strNames, strValues);
    }

    static std::string UPDATE_TABLE(
        const char *tableName,
        const int &_id,
       std::vector<std::string> names,
       std::vector<std::string> values)
    {
       std::string os;
       std::string partSql;
        dmlCat(partSql, names.begin(), values.begin(), names, values);
        os
            << "UPDATE "
            << tableName << " "
            << "SET "
            << partSql << " "
            << "WHERE _ID = "
            << _id;
        return os;
    }

    static std::string SELECT(const char *tableName, int count)
    {
       std::string os;
        std::string limit = "";
        if (count > 0)
        {
            limit += " LIMIT " + to_string(count);
        }
        os
            << "SELECT * FROM "
            << tableName
            << limit;
        return os;
    }

    static std::string SELECT(const char *tableName, const Filter &filter, int count)
    {
       std::string os;
        std::string limit = "";
        if (count > 0)
        {
            limit += " LIMIT " + to_string(count);
        }
        os
            << "SELECT * FROM "
            << tableName
            << " "
            << WHERE(filter)
            << limit;
        return os;
    }

    static std::string SELECT(const char *tableName, const std::string &sqlFilter, int count)
    {
       std::string os;
        std::string limit = "";
        auto where = [](const std::string& filter)
        {
            if(filter.size() > 0)
                return "WHERE " << filter;
            else
                return std::string("");
        };
        if (count > 0)
        {
            limit += " LIMIT " + to_string(count);
        }
        os
            << "SELECT * FROM "
            << tableName
            << " "
            << where(sqlFilter)
            << limit;
        return os;
    }

    static std::string SELECT(const char *tableName, const std::string &sqlFilter, const std::string &sqlSort, int count)
    {
       std::string os;
        std::string limit = "";
        auto where = [](const std::string& filter)
        {
            if(filter.size() > 0)
                return "WHERE " << filter;
            else
                return std::string("");
        };
        auto orderBy = [](const std::string& sort)
        {
            if(sort.size() > 0)
                return "ORDER BY " << sort;
            else
                return std::string("");
        };
        if (count > 0)
        {
            limit += " LIMIT " + to_string(count);
        }
        os
            << "SELECT * FROM "
            << tableName
            << " "
            << where(sqlFilter)
            << " "
            << orderBy(sqlSort)
            << limit;
        return os;
    }

    static std::string SELECT(const char *tableName, const std::string &joinCondition, const Filter &filter, int count)
    {
       std::string os;
        std::string limit = "";
        if (count > 0)
        {
            limit += " LIMIT " + to_string(count);
        }
        os
            << "SELECT * FROM "
            << tableName
            << " INNER JOIN "
            << joinCondition
            << " "
            << WHERE(filter)
            << limit;
        return os;
    }

    static std::string DELETE(const char *tableName, const int &_id)
    {
       std::string os;

        os
            << "DELETE FROM "
            << tableName << " "
            << "WHERE _ID = "
            << _id;
        return os;
    }

    static std::string DELETE(const char *tableName, const std::string& sqlFilter)
    {
       std::string os;

        os
            << "DELETE FROM "
            << tableName << " "
            << "WHERE "
            << sqlFilter;
        return os;
    }
};

#endif //SQLFACTORY_H
