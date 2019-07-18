#ifndef DBCACHE_H
#define DBCACHE_H

#include <map>
#include <memory>
#include "datadefinition.h"
#include "catalogue.h"
#include "master.h"
// #include "charmap.h"
// #include "logger.h"


static uint32_t getHash(const std::string &compound, const uint8_t &sz)
{
    /****https://tools.ietf.org//html/draft-eastlake-fnv-15****/
    const uint32_t initialFNV = 2166136261U;
    const uint32_t fnvPrime = 16777619; //709607;
    uint32_t hash = initialFNV;
    for (uint32_t i = 0; i < sz; i++)
    {
        hash = hash ^ (compound[i]);
        hash = hash * fnvPrime;
    }
    return hash;
}
struct Cache
{
private:
    int m_hash;
    schema m_schema;
    bool m_isSchemaSet = false;
public:
    Cache(const int &argHash) : m_hash{argHash}
    {
    }
    Cache(const int &argHash, const schema &schm) :
        m_hash{argHash},
        m_schema{schm},
        m_isSchemaSet{true}
    {
    }
    int getHash()
    {
        return m_hash;
    }
    void updateHash(const int& hash)
    {
        m_hash = hash;
    }
    schema* getSchema()
    {
        if(m_isSchemaSet){
            return &m_schema;
        }
        else {
            return nullptr;
        }
    }
    void setSchema(const schema& schma)
    {
        m_isSchemaSet = true;
        m_schema = schma;
    }
};
class DBCache
{
#define SYS_CACHE Catalogue(m_db, "_sys_cache", schmSysCache)

    const schema schmSysCache = {
        {"name", PLAT_STR},
        {"catalogue", PLAT_STR},
        {"hash", PLAT_INT}};

    DBCache(const char *name, const char *db);
    const char *m_name;
    const char *m_db;
    inline Cache* getCacheForTable(const char* tableName)
    {
        auto itFind = m_catalogueHCache.find(tableName);
        if(itFind != m_catalogueHCache.end())
        {
            return itFind->second.get();
        }
        else {
            return nullptr;
        }
    }

    inline void createCacheForTable(const char* tableName, const int& hash)
    {
        m_catalogueHCache
                .insert(
                    make_pair(tableName,
                              std::unique_ptr<Cache>(
                                  new Cache(hash))));
    }

    inline void createCacheForTable(const char* tableName, const int& hash, const schema& schm)
    {
        m_catalogueHCache
                .insert(
                    make_pair(tableName,
                              std::unique_ptr<Cache>(
                                  new Cache(hash, schm))));
    }

    std::map<std::string, std::unique_ptr<Cache>> m_catalogueHCache;
    

    static const char *m_current;
    static std::unique_ptr<DBCache> s_cache;
    void setHash(const char *tableName, const int &hash, const schema &schm);
    int verifyAndSaveHash(const char *tableName, const schema &schm);

public:
    static inline uint32_t createHashForSchema(const char *tableName, const schema &schm)
    {
       std::string compound(tableName);
        for (const std::pair<const char *, PlatformTypeEnum> &pair : schm)
        {
            compound
                    .append(pair.first)
                    .append(std::to_string(pair.second));
        }
        return getHash(compound, compound.size());
    }

    static DBCache &Current()
    {
        return *s_cache;
    }

    static DBCache &Select(const char *name, const char *db)
    {
        s_cache = std::unique_ptr<DBCache>(new DBCache(name, db));
        m_current = name;
        return *s_cache;
    }
    DBCache &AddTable(const char *tableName, const schema &schm);
    DBCache &AddMaster(Master &master);

    int Get(const char *name, std::unique_ptr<Catalogue> &catalogue);
};

#endif //DBCACHE_H
