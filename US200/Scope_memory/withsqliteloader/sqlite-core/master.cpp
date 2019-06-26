#include "master.h"

Master::Master(const char *table, const schema &sch) : m_table{table}, m_schema{sch} {}

Master &Master::Save(const char *db)
{
    Catalogue master(db, m_table, m_schema);
    for (auto &vecTVal : m_rows)
    {
        int i = 0;
        for (auto &pair : m_schema)
        {
            if ((vecTVal.size() <= i) || (vecTVal[i].m_isNull))
            {
                i += 1;
                continue;
            }

            switch (pair.second)
            {
            case PLAT_BOOL:
                master.Set(pair.first, vecTVal[i].m_bool);
                break;
            case PLAT_DT:
                master.Set(pair.first, vecTVal[i].m_dt);
                break;
            case PLAT_DBL:
                master.Set(pair.first, vecTVal[i].m_double);
                break;
            case PLAT_INT:
                master.Set(pair.first, vecTVal[i].m_int);
                break;
            case PLAT_STR:
                master.Set(pair.first, vecTVal[i].m_string);
                break;
            default:
                break;
            }
            i += 1;
        }
        master.Save();
    }
    return *this;
}
