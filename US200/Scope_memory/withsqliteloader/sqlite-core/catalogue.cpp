#include "catalogue.h"

Catalogue::Catalogue(const char *db, const char *table, const schema &schm) : PersistableBase(db, table),
    m_schema{schm}
{
}
Catalogue::Catalogue(const char *db, const char *table) : PersistableBase(db, table)
{
}
Columns &Catalogue::getDataBuffer()
{
    return m_buffer;
}
void Catalogue::onSave(const int &id)
{
    std::ignore = id;         // UNUSED parameter 'id'
    m_buffer.clear();
}
void Catalogue::onSetData()
{
    swap(m_buffer);
}

void Catalogue::onGetData(Columns &cols)
{
    m_buffer.swap(cols);
}

schema Catalogue::getSchema() const
{
    return m_schema;
}
std::vector<Catalogue> Catalogue::All()
{
    return Select("");
}
Catalogue Catalogue::First()
{
    return PersistableBase::First(*this);
}
Catalogue Catalogue::First(const std::string &sqlFilter)
{
    return PersistableBase::First(*this, sqlFilter);
}
Catalogue Catalogue::First(const Filter &filter)
{
    return PersistableBase::First(*this, filter);
}

std::unique_ptr<Catalogue> Catalogue::First_UP(const Filter &filter)
{
    return PersistableBase::First_UP(*this, filter);
}
std::vector<Catalogue> Catalogue::Select(const std::string &sqlFilter)
{
    return PersistableBase::Select(*this, sqlFilter);
}
std::vector<Catalogue> Catalogue::Select(const Filter &filter)
{
    return PersistableBase::Select(*this, filter);
}
up_vec_catalogue Catalogue::Select_UP(const std::string &sqlFilter)
{
    return PersistableBase::Select_UP(*this, sqlFilter);
}
up_vec_catalogue Catalogue::Select_UP(const Filter &filter)
{
    return PersistableBase::Select_UP(*this, filter);
}
int Catalogue::Delete(const std::string &sqlFilter) const
{
    return remove(sqlFilter);
}
