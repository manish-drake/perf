#ifndef CATALOGUE_H
#define CATALOGUE_H

#include "persistablebase.h"
#include "datetime.h"
#include <stdlib.h>

class Catalogue;
typedef std::unique_ptr<Catalogue> up_catalogue;
typedef std::unique_ptr<std::vector<up_catalogue>> up_vec_catalogue;

class Catalogue : public PersistableBase
{
    schema m_schema;
    ColumnsItem m_buffer;

  public:
    Catalogue(const char *db, const char *table, const schema &schm);
    Catalogue(const char *db, const char *table);

    
    void Set(const char *key, const std::string &value)
    {
        if (m_schema[key] == PLAT_STR)
            m_buffer.Set(key, value);
        else
            Set(key, atoi(value.c_str()));
    }
    void Set(const char *key, const char *value)
    {
        Set(key,std::string(strdup(value)));
    }
    void Set(const char *key, const Datetime &value)
    {
        m_buffer.Set(key, value);
    }
    void Set(const char *key, std::nullptr_t value)
    {
        std::ignore = key;         // UNUSED parameter 'key'
        std::ignore = value;         // UNUSED parameter 'value'
    }
    
    template <typename T>
    void Set(const char *key, const T &value)
    {
        switch (m_schema[key])
        {
        case PLAT_STR:
        {
            m_buffer.Set(key, to_string(value));
            break;
        }
        case PLAT_DBL:
        {
            m_buffer.Set(key, (double)value);
            break;
        }
        case PLAT_INT:
        {
            m_buffer.Set(key, (int)value);
            break;
        }
        case PLAT_BOOL:
        {
            m_buffer.Set(key, (bool)value);
            break;
        }
        case PLAT_DT:
        {
            m_buffer.Set(key, (Datetime)value);
        }
        }
    }

    Columns &getDataBuffer() override;
    void onSave(const int &id) override;
    void onSetData();
    void onGetData(Columns &cols);
    schema getSchema() const;
   std::vector<Catalogue> All();
    Catalogue First();
    Catalogue First(const Filter &filter);
    Catalogue First(const std::string &sqlFilter);
    std::unique_ptr<Catalogue> First_UP(const Filter &filter);
   std::vector<Catalogue> Select(const std::string &sqlFilter);
   std::vector<Catalogue> Select(const Filter &filter);
    up_vec_catalogue Select_UP(const std::string &sqlFilter);
    up_vec_catalogue Select_UP(const Filter &filter);
    int Delete(const std::string &sqlFilter) const;
};

#endif //CATALOGUE_H
