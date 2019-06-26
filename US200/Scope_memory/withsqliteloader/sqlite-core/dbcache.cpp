#include "dbcache.h"
#include "table.h"

std::unique_ptr<DBCache> DBCache::s_cache = nullptr;
const char *DBCache::m_current;

DBCache::DBCache(const char *name, const char *db) : m_name{name},
    m_db{db}
{
    auto cache = SYS_CACHE.Select_UP(apply_filter("name", m_name));
    for (auto &table : *cache)
    {
        char *tableName = strdup(table->getString("catalogue").c_str());
        createCacheForTable(tableName, table->getInt("hash"));
        free ((char*)tableName);
    }
}

void DBCache::setHash(const char *tableName, const int32_t &hash, const schema &schm)
{
    if (auto pCache = getCacheForTable(tableName))
    {
        //exists: update hash in db
        // Logger::Instance()->Log(Level::Info, "dbCache", "hash found for: %s (update hash)", tableName);
        auto cache = SYS_CACHE.First(
                    apply_filter("name", m_name)
                    .AND()
                    .apply_filter("catalogue", tableName));
        cache.Set("hash", hash);
        cache.Update();
        //exists: replace in Catalogue hash
        pCache->updateHash(hash);
        pCache->setSchema(schm);
    }
    else
    {
        //does not exist: add hash in db
        // Logger::Instance()->Log(Level::Info, "dbCache", "hash not found for: %s (add hash)", tableName);
        auto cache = SYS_CACHE;
        cache.Set("name", m_name);
        cache.Set("catalogue", tableName);
        cache.Set("hash", hash);
        cache.Save();
        //does not exist: add hash to Catalogue hash
        createCacheForTable(tableName, hash, schm);
    }
}

int DBCache::Get(const char *name, std::unique_ptr<Catalogue> &catalogue)
{
    if (auto pCache = getCacheForTable(name))
    {
        catalogue = std::unique_ptr<Catalogue>(
                        new Catalogue(m_db, name, *pCache->getSchema()));
        return -1;
    }
    return 0;
}
int DBCache::verifyAndSaveHash(const char *tableName, const schema &schm)
{
    int hash = createHashForSchema(tableName, schm);
    auto pCache = getCacheForTable(tableName);
    if (!pCache) //No hash exists: Cache does not know about this table
    {
        // Logger::Instance()->Log(Level::Warn, "dbCache", "No hash exists: Cache does not know about this table: %s", tableName);
        Catalogue table(m_db, tableName, schm);
        PersistableBase::Create(table); //Create new table
        setHash(tableName, hash, schm);       //Save hash
        return 1;
    }
    else if (pCache->getHash() != hash) //Hash exists but is not the same as earlier: Schema changed
    {
        // Logger::Instance()->Log(Level::Warn, "dbCache", "Hash exists but is not the same as earlier: Schema changed: %s", tableName);
        Catalogue table(m_db, tableName, schm);
        PersistableBase::Create(table, true); //Delete old table and create again
        setHash(tableName, hash, schm);             //Save hash
        return -1;
    }
    else if(!pCache->getSchema())// Cache from sys_cache table, with not yet initialized schema
    {
        pCache->setSchema(schm);
    }
    return 0;
}

DBCache &DBCache::AddTable(const char *tableName, const schema &schm) //Initialize schema in Cache
{    
    verifyAndSaveHash(tableName, schm);
    return *this;
}

DBCache &DBCache::AddMaster(Master &master)
{
    if (verifyAndSaveHash(master.Table(), master.Schema()))
        master.Save(m_db);
    return *this;
}
