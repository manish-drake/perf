#include "table.h"
#include "sqlscripthelper.h"
#include "filter.h"
#include <cmath>

Table::Table(const char *tableName, const DB &db) : m_name{tableName}, m_db{db}
{
}

Table::Table(const char *tableName, const char *dbName) : m_name{tableName}, m_db{dbName} {}

bool Table::exists() const
{
    if (!m_db.istableTouched(m_name))
    {
       std::string sql = SqlScriptHelper::TABLE_EXISTS(m_name);
        int count = m_db.selectCount(sql.data());
        bool doesExist = count >= 0;

        if (doesExist)
            m_db.istableTouched(m_name);

        return doesExist;
    }
    else
    {
        return true;
    }
}

int Table::add(const std::vector<DBField> &fields)
{
    if (exists())
    {
        m_db.tableTouched(m_name);
        return -1;
    }
    else
    {
       std::vector<DBField> newTable(fields);
        newTable.push_back(DBField("_ID", SQL_INT, true));
       std::string &&sqlCreateTable = SqlScriptHelper::CREATE_TABLE(m_name, newTable);
        if (!m_db.execScalar(sqlCreateTable.data()))
        {
            m_db.tableTouched(m_name);
        }
    }
    return 0;
}

int Table::create(const std::vector<SqlUnit> &sqlUnits)
{
    if (exists())
    {
       std::vector<std::string> names, values;
        for (const SqlUnit &val : sqlUnits)
        {
            names.push_back(val.Name);
            values.push_back(SqlScriptHelper::treatSqlUnit(val.toString(), val.Tp));
        }
       std::string &&sqlInsertTable = SqlScriptHelper::INSERT_TABLE(m_name, names, values);
        return m_db.execScalar(sqlInsertTable.data());
    }
    else
    {
        return -1;
    }
}

int Table::update(const int &_id, const std::vector<SqlUnit> &sqlUnits)
{
    if (exists())
    {
       std::vector<std::string> names, values;
        for (const SqlUnit &val : sqlUnits)
        {
            names.push_back(val.Name);
            values.push_back(SqlScriptHelper::treatSqlUnit(val.toString(), val.Tp));
        }
       std::string &&sqlUpdateTable = SqlScriptHelper::UPDATE_TABLE(m_name, _id, names, values);
        return m_db.execScalar(sqlUpdateTable.data());
    }
    else
    {
        return -1;
    }
}

int Table::read(sqlResult &results, int limit) const
{
    if (exists())
    {
       std::string selectSql = SqlScriptHelper::SELECT(m_name, limit);
        return m_db.select(selectSql.data(), results);
    }
    else
    {
        return -1;
    }
}

int Table::read(sqlResult &results, const Filter &filter, int limit) const
{
    if (exists())
    {
       std::string selectSql = SqlScriptHelper::SELECT(m_name, filter, limit);
        return m_db.select(selectSql.data(), results);
    }
    else
    {
        return -1;
    }
}

int Table::read(sqlResult &results, const std::string &sqlFilter, int limit) const
{
    if (exists())
    {
       std::string selectSql = SqlScriptHelper::SELECT(m_name, sqlFilter, limit);
        return m_db.select(selectSql.data(), results);
    }
    else
    {
        return -1;
    }
}

int Table::read(sqlResult &results, const std::string &sqlFilter, const std::string &sqlSort, int limit) const
{
    if (exists())
    {
       std::string selectSql = SqlScriptHelper::SELECT(m_name, sqlFilter, sqlSort, limit);
        return m_db.select(selectSql.data(), results);
    }
    else
    {
        return -1;
    }
}

int Table::read(sqlResult &results, const std::string &joinCondition, const Filter &filter, int limit) const
{
    if (exists())
    {
       std::string selectSql = SqlScriptHelper::SELECT(m_name, joinCondition, filter, limit);
        return m_db.select(selectSql.data(), results);
    }
    else
    {
        return -1;
    }
}

int Table::del(const int &_id) const
{
    if (exists())
    {
       std::string removeSql = SqlScriptHelper::DELETE(m_name, _id);
        return m_db.execScalar(removeSql.data());
    }
    else
    {
        return -1;
    }
}

int Table::del(const std::string &sqlFilter) const
{
    if (exists())
    {
       std::string removeSql = SqlScriptHelper::DELETE(m_name, sqlFilter);
        return m_db.execScalar(removeSql.data());
    }
    else
    {
        return -1;
    }
}
int Table::drop()
{
    if (exists())
    {
       std::string dropSql = SqlScriptHelper::DROP_TABLE(m_name);
        return m_dropped = m_db.execScalar(dropSql.data());
    }
    else
    {
        return -1;
    }
}
