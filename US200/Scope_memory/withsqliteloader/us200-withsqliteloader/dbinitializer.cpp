#include "dbinitializer.h"
#include "dbcache.h"

DBInitializer::DBInitializer()
{

}

void DBInitializer::initializeDBCache()
{
    DBCache::Select("us200","us200.db");

    DBCache::Current().AddTable("navigation",
    {
        {"prevPath", PLAT_STR},
        {"nextPath", PLAT_STR},
        {"currentPath", PLAT_STR}
    });

}
