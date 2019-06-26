#include "persistablebase.h"
#include "databroker.h"

PersistableBase::PersistableBase(const char *dbName, const char *tableName)
    : m_table(tableName, dbName), m__id{0}
{
}
bool PersistableBase::tableExists() const
{
    return m_table.exists();
}
Columns &PersistableBase::getDataBuffer()
{
    return *this;
}
void PersistableBase::Save()
{
    this->onSetData();
    Columns &buffer = this->getDataBuffer();
    try
    {
       std::vector<SqlUnit> sqlUnits;
        SqlUnitCollection::create(buffer, getSchema(), sqlUnits);

        PersistableBase::Create(*this);

        m__id = m_table.create(sqlUnits);
        clear();
        onSave(m__id);
    }
    catch (std::exception e)
    {
        throw e;
    }
}

void PersistableBase::Remove()
{
    if (m__id > 0)
    {
        m_table.del(m__id);
    }
}

void PersistableBase::Update()
{
    onSetData();
    Columns &buffer = this->getDataBuffer();
   std::vector<SqlUnit> sqlUnits;
    SqlUnitCollection::create(buffer, getSchema(), sqlUnits);

    m_table.update(m__id, sqlUnits);
    clear();
}

up_columns PersistableBase::first()
{
    sqlResult results;
    int rows = m_table.read(results, 1);
    if (rows > 0)
    {
        up_columns &&cols = ColumnsCollection::create(getSchema(), results[0]);

        return move(cols);
    }
    else
    {
        return up_columns(nullptr);
    }
}
up_columns PersistableBase::first(const std::string &sqlFilter)
{
    sqlResult results;
    int rows = m_table.read(results, sqlFilter, 1);
    if (rows > 0)
    {
        up_columns &&cols = ColumnsCollection::create(getSchema(), results[0]);

        return move(cols);
    }
    else
    {
        return up_columns(nullptr);
    }
}
up_columns PersistableBase::first(const Filter &filter)
{
    sqlResult results;
    int rows = m_table.read(results, filter, 1);
    if (rows > 0)
    {
        up_columns &&cols = ColumnsCollection::create(getSchema(), results[0]);

        return move(cols);
    }
    else
    {
        return up_columns(nullptr);
    }
}

up_columns PersistableBase::last()
{
    return first();
}

up_vecols PersistableBase::all()
{
    up_vecols vec(new std::vector<up_columns>);
    sqlResult results;
    m_table.read(results);
    for (const std::vector<SqlUnit> &row : results)
    {
        up_columns cols = ColumnsCollection::create(getSchema(), row);

        vec->push_back(std::move(cols));
    }
    return vec;
}

up_vecols PersistableBase::select(const Filter &filter) const
{
    up_vecols vec(new std::vector<up_columns>);
    sqlResult results;
    m_table.read(results, filter);
    for (const std::vector<SqlUnit> &row : results)
    {
        up_columns cols = ColumnsCollection::create(getSchema(), row);

        vec->push_back(std::move(cols));
    }
    return vec;
}
up_vecols PersistableBase::select(const std::string &sqlFilter) const
{
    up_vecols vec(new std::vector<up_columns>);
    sqlResult results;
    m_table.read(results, sqlFilter);
    for (const std::vector<SqlUnit> &row : results)
    {
        const schema &schm = getSchema();
        up_columns cols = ColumnsCollection::create(schm, row);

        vec->push_back(std::move(cols));
    }
    return vec;
}
up_vecols PersistableBase::select(const std::string &sqlFilter, const std::string &sqlSort) const
{
    up_vecols vec(new std::vector<up_columns>);
    sqlResult results;
    m_table.read(results, sqlFilter, sqlSort);
    for (const std::vector<SqlUnit> &row : results)
    {
        const schema &schm = getSchema();
        up_columns cols = ColumnsCollection::create(schm, row);

        vec->push_back(std::move(cols));
    }
    return vec;
}
up_vecols PersistableBase::select(const std::string &joinCondition, const Filter &filter) const
{
    up_vecols vec(new std::vector<up_columns>);
    sqlResult results;
    m_table.read(results, joinCondition, filter);
    for (const std::vector<SqlUnit> &row : results)
    {
        up_columns cols = ColumnsCollection::create(getSchema(), row);

        vec->push_back(std::move(cols));
    }
    return vec;
}
int PersistableBase::remove(const std::string &sqlFilter) const
{
    return m_table.del(sqlFilter);
}
