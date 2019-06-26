#ifndef PERSIST_H
#define PERSIST_H

#include <utility>
#include "columns.h"
#include "table.h"
#include "filter.h"
#include "databroker.h"

class Table;
/**
 * The base class for any data type that we want to save
 * to database. The class can be decomposed further to
 * derive policies related to saving data and then
 * initializing user defined data objects from basic types.
*/
class PersistableBase : public Columns
{
private:
    Table m_table;
    int m__id;

protected:
    PersistableBase(Table t) : m_table(t) {}
    bool tableExists() const;
    virtual void onSetData() = 0;
    virtual void onGetData(Columns &col) = 0;
    virtual Columns &getDataBuffer();
    inline virtual void onSave(const int &id)
    {
        std::ignore = id; // UNUSED parameter 'id'
    }

    /**
     * Helper function that returns firstl value from db
    */
    up_columns first();
    up_columns first(const std::string &sqlFilter);
    up_columns first(const Filter &filter);
    /**
     * Helper function that returns last value from db
    */
    up_columns last();
    /**
     * Helper function that returns all values from db
    */
    up_vecols all();
    /**
     * Helper function that returns all values from db qualifying a filter
    */
    up_vecols select(const Filter &filter) const;
    /**
     * Helper function that returns all values from db qualifying a filter
    */
    up_vecols select(const std::string &sqlFilter) const;
    /**
     * Helper function that returns all values from db qualifying a filter and sort
    */
    up_vecols select(const std::string &sqlFilter, const std::string &sqlSort) const;
    /**
     * Helper function that returns all values from db qualifying inner join and a filter
    */
    up_vecols select(const std::string &joinCondition, const Filter &filter) const;
    /**
     * Helper function that removes all entries in the DB qualifying a filter
    */
    int remove(const std::string &sqlFilter) const;

public:
    PersistableBase(const char *dbName, const char *tableName);
    void Save();
    void Update();
    void Remove();
    bool IsSchemaEmpty();
    inline int _ID() const
    {
        return m__id;
    }
    inline void set_ID(const int &id)
    {
        m__id = id;
    }

    static int Delete(PersistableBase &persistableBase)
    {
        return persistableBase.m_table.drop();
    }

    static int Create(PersistableBase &persistableBase, bool overwrite = false)
    {
        if (persistableBase.m_table.exists())
        {
            if (overwrite)
                Delete(persistableBase);
            else
                return -1;
        }
        std::vector<DBField> dbFieldCollection;
        DBFieldCollection::create(persistableBase.getSchema(), dbFieldCollection);
        persistableBase.m_table.add(dbFieldCollection);
        return 0;
    }

    // static std::vector<PersistableBase> Select(PersistableBase &persistable)
    // {
    //    std::vector<PersistableBase> vec;
    //     unique_ptr<vector<unique_ptr<Columns>>> cols = persistable.all();
    //     for (const up_columns &col : *cols)
    //     {
    //         PersistableBase item(persistable);
    //         item.onGetData(*col);
    //         col->get(item.m__id, "_ID");
    //         item.onSetData();
    //         vec.push_back(item);
    //     }
    //     return vec;
    // }
    template <typename t>
    static void persistableFromColumns(Columns &columns, t &item)
    {
        item.onGetData(columns);
        PersistableBase &e = item;
        columns.get(e.m__id, "_ID");
        e.onSetData();
    }
    template <class t>
    static std::vector<t> Select(t persistable)
    {
        std::vector<t> vec;
        std::unique_ptr<std::vector<std::unique_ptr<Columns>>> cols = persistable.all();
        for (const up_columns &col : *cols)
        {
            t item(persistable);
            persistableFromColumns(*col, item);
            vec.push_back(item);
        }
        return vec;
    }

    template <class t>
    static std::unique_ptr<std::vector<std::unique_ptr<t>>> Select_UP(t persistable)
    {
        std::unique_ptr<std::vector<std::unique_ptr<t>>> up_vec(new std::vector<std::unique_ptr<t>>);
        up_vecols cols = persistable.all();
        for (const up_columns &col : *cols)
        {
            std::unique_ptr<t> item(new t(persistable));
            persistableFromColumns(*col, *item);
            up_vec->push_back(std::move(item));
        }
        return up_vec;
    }

    template <class t>
    static std::vector<t> Select(t persistable, const Filter &filter)
    {
        std::vector<t> vec;
        up_vecols cols = persistable.select(filter);
        for (up_columns &col : *cols)
        {
            t item(persistable);
            persistableFromColumns(*col, item);
            vec.push_back(item);
        }
        return vec;
    }

    template <class t>
    static std::vector<t> Select(t persistable, const std::string &sqlFilter)
    {
        std::vector<t> vec;
        up_vecols cols = persistable.select(sqlFilter);
        for (up_columns &col : *cols)
        {
            t item(persistable);
            persistableFromColumns(*col, item);
            vec.push_back(item);
        }
        return vec;
    }

    template <class t>
    static std::vector<t> Select(t persistable, const std::string &sqlFilter, const std::string &sqlSort)
    {
        std::vector<t> vec;
        up_vecols cols = persistable.select(sqlFilter, sqlSort);
        for (up_columns &col : *cols)
        {
            t item(persistable);
            persistableFromColumns(*col, item);
            vec.push_back(item);
        }
        return vec;
    }

    template <class t>
    static std::unique_ptr<std::vector<std::unique_ptr<t>>> Select_UP(t persistable, const Filter &filter)
    {
        std::unique_ptr<std::vector<std::unique_ptr<t>>> up_vec(new std::vector<std::unique_ptr<t>>);
        up_vecols cols = persistable.select(filter);
        for (up_columns &col : *cols)
        {
            std::unique_ptr<t> item(new t(persistable));
            persistableFromColumns(*col, *item);
            up_vec->push_back(std::move(item));
        }
        return up_vec;
    }

    template <class t>
    static std::unique_ptr<std::vector<std::unique_ptr<t>>> Select_UP(t persistable, const std::string &sqlFilter)
    {
        std::unique_ptr<std::vector<std::unique_ptr<t>>> up_vec(new std::vector<std::unique_ptr<t>>);
        up_vecols cols = persistable.select(sqlFilter);
        for (up_columns &col : *cols)
        {
            std::unique_ptr<t> item(new t(persistable));
            persistableFromColumns(*col, *item);
            up_vec->push_back(std::move(item));
        }
        return up_vec;
    }

    template <class t>
    static std::unique_ptr<std::vector<std::unique_ptr<t>>> Select_UP(t persistable, const std::string &sqlFilter, const std::string &sqlSort)
    {
        std::unique_ptr<std::vector<std::unique_ptr<t>>> up_vec(new std::vector<std::unique_ptr<t>>);
        up_vecols cols = persistable.select(sqlFilter, sqlSort);
        for (up_columns &col : *cols)
        {
            std::unique_ptr<t> item(new t(persistable));
            persistableFromColumns(*col, *item);
            up_vec->push_back(std::move(item));
        }
        return up_vec;
    }

    template <class t>
    static std::unique_ptr<std::vector<std::unique_ptr<t>>> Select_UP(t persistable, const std::string &joinCondition, const Filter &filter)
    {
        std::unique_ptr<std::vector<std::unique_ptr<t>>> up_vec(new std::vector<std::unique_ptr<t>>);
        up_vecols cols = persistable.select(joinCondition, filter);
        for (up_columns &col : *cols)
        {
            std::unique_ptr<t> item(new t(persistable));
            persistableFromColumns(*col, *item);
            up_vec->push_back(std::move(item));
        }
        return up_vec;
    }

    template <class t>
    static t First(t persistable, const std::string &sqlFilter)
    {
        up_columns col = persistable.first(sqlFilter);
        if(col)
        {
            t item(persistable);
            persistableFromColumns(*col, item);
            return item;
        }
        else {
            return t(persistable);
        }
    }

    template <class t>
    static t First(t persistable, const Filter &filter)
    {
        up_columns col = persistable.first(filter);
        if(col)
        {
            t item(persistable);
            persistableFromColumns(*col, item);
            return item;
        }
        else {
            return t(persistable);
        }
    }

    template <class t>
    static t First(t persistable)
    {
        up_columns col = persistable.first();
        if(col)
        {
            t item(persistable);
            persistableFromColumns(*col, item);
            return item;
        }
        else {
            return t(persistable);
        }
    }
    template <class t>
    static std::unique_ptr<t> First_UP(t &persistable)
    {
        up_columns col = persistable.first();
        if(col){
            std::unique_ptr<t> item(new t(persistable));
            persistableFromColumns(*col, *item);
            return item;
        }
        else {
            return std::unique_ptr<t>(nullptr);
        }
    }
    template <class t>
    static std::unique_ptr<t> First_UP(t persistable, const Filter &filter)
    {
        up_columns col = persistable.first(filter);
        if(col)
        {
            std::unique_ptr<t> item(new t(persistable));
            persistableFromColumns(*col, *item);
            return item;
        }
        else {
            return std::unique_ptr<t>(nullptr);
        }
    }

    template <class t>
    static void Update(t persistable, const Filter &filter, const std::map<std::string,std::string> &changes)
    {
    }

    template <class t>
    static void Remove(t persistable, const std::string &filter)
    {
        persistable.remove(filter);
    }
};

#endif // PERSIST_H
