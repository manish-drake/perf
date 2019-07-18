#include "db.h"
//#include <sqlite3.h>
#include <stdio.h>
//#include <memory>
#include <string.h>
#include <algorithm>
//#include "logger.h"

tableJournal DB::g_tableJournal;
DB::DB(const char *name) : m_name{name}
{
}

void DB::tableTouched(const char *tableName)
{
    std::string strTableName = std::string(tableName);
    tableJournal::const_iterator find = g_tableJournal.find(m_name);
    if (find == g_tableJournal.end())
    {
        g_tableJournal.insert(make_pair(m_name, std::vector<std::string>()));
    }
    std::vector<std::string> &tablesList = g_tableJournal[m_name];
    if (std::find(tablesList.begin(), tablesList.end(), strTableName) == tablesList.end())
    {
        tablesList.push_back(strTableName);
    }
}

bool DB::istableTouched(const char *tableName) const
{
    std::string strTableName = std::string(tableName);
    tableJournal::iterator find = g_tableJournal.find(m_name);
    if (find != g_tableJournal.end())
    {
        std::vector<std::string> tablesList = g_tableJournal[m_name];
        if (std::find(tablesList.begin(), tablesList.end(), strTableName) != tablesList.end())
        {
            return true;
        }
    }
    return false;
}

int DB::callback(void *data, int argc, char **argv, char **azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char *)data);

    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}
sqldb DB::create() const
{
    sqlite3 *db;
    int rc = sqlite3_open(m_name, &db);
    sqldb up_db{db};
    if (rc)
    {
        up_db.reset();
    }
    return up_db;
}
int DB::getLastRowID(const sqldb &db) const
{
    sqlite3_stmt *stmt;
    sqlite3_prepare(db.get(), "SELECT last_insert_rowid()", -1, &stmt, NULL);

    sqlstmt up_stmt{stmt};

    if (sqlite3_step(up_stmt.get()) == SQLITE_ROW)
    {
        return sqlite3_column_int(up_stmt.get(), 0);
    }
    else
    {
        return 0;
    }
}

int DB::execScalar(const char *sql) const
{
    char *err_msg = 0;
    sqldb db = create();

    int rc = sqlite3_exec(db.get(), sql, callback, 0, &err_msg);

    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    }
    else
    {
        fprintf(stdout, "query executed successfully\n");
    }
    int rowID = getLastRowID(db);
    return rowID;
}

int DB::selectCount(const char *sql) const
{
    sqldb db = create();
    sqlite3_stmt *stmt;
    sqlite3_prepare(db.get(), sql, -1, &stmt, NULL);
    sqlstmt up_stmt{stmt};
    int rows = -1;
    while (sqlite3_step(up_stmt.get()) == SQLITE_ROW)
    {
        rows++;
    }
    return rows;
}

int DB::selectFirstColumn(const char *sql, SqlUnit &sqlUnit) const
{
    sqldb db = create();
    sqlite3_stmt *stmt;
    sqlite3_prepare(db.get(), sql, -1, &stmt, NULL);
    sqlstmt up_stmt{stmt};
    if (sqlite3_step(up_stmt.get()) == SQLITE_ROW)
    {
        const char *colName = sqlite3_column_name(up_stmt.get(), 0);
        switch (sqlite3_column_type(up_stmt.get(), 0))
        {
        case SQLITE_INTEGER:
        {
            sqlUnit = SqlUnit(colName, sqlite3_column_int(up_stmt.get(), 0));
            break;
        }
        case SQLITE_FLOAT:
        {
            sqlUnit = SqlUnit(colName, (double)sqlite3_column_double(up_stmt.get(), 0));
            break;
        }
        case SQLITE_TEXT:
        {
            const unsigned char *ucharVal = sqlite3_column_text(up_stmt.get(), 0);
            std::string strVal = reinterpret_cast<const char *>(ucharVal);
            sqlUnit = SqlUnit(colName, strVal);
            break;
        }
//            case SQLITE_BLOB:  Logger::Instance()->Log(Level::Info, "db-selectScalar", "BLOB");
//                Logger::Instance()->Log(Level::Info, "db-selectScalar", "Size of blob: %i", sqlite3_column_bytes(up_stmt.get(), col));
//                 struct tm *blobRetreived;
//                 blobRetreived = (struct tm *) sqlite3_column_blob(up_stmt.get(), col);
//                 Logger::Instance()->Log(Level::Info, "db-selectScalar", "Year retrieved from blob: %s", blobRetreived->tm_year+1900);
//                 break;
        case SQLITE_NULL:
        {
            sqlUnit = SqlUnit(colName);
            break;
        }
        default:
            break;
        }
        return 1;
    }
    else
    {
        return 0;
    }
}

int DB::select(const char *sql, sqlResult &result) const
{
    sqldb db = create();

    result.clear();
    sqlite3_stmt *stmt;
    sqlite3_prepare(db.get(), sql, -1, &stmt, NULL);
    sqlstmt up_stmt{stmt};
    int rows = 0;
    while (sqlite3_step(up_stmt.get()) == SQLITE_ROW)
    {
        rows++;
        std::vector<SqlUnit> row;
        for (int col = 0; col < sqlite3_column_count(up_stmt.get()); col++)
        {
            const char *colName = strdup(sqlite3_column_name(up_stmt.get(), col));
            switch (sqlite3_column_type(up_stmt.get(), col))
            {
            case SQLITE_INTEGER:
            {
                row.push_back(SqlUnit(colName, sqlite3_column_int(up_stmt.get(), col)));
                break;
            }
            case SQLITE_FLOAT:
            {
                row.push_back(SqlUnit(colName, (double)sqlite3_column_double(up_stmt.get(), col)));
                break;
            }
            case SQLITE_TEXT:
            {
                const unsigned char *ucharVal = sqlite3_column_text(up_stmt.get(), col);
                std::string strVal(reinterpret_cast<const char *>(ucharVal));
                row.push_back(SqlUnit(colName, strVal));
                break;
            }
            //    case SQLITE_BLOB:    Logger::Instance()->Log(Level::Info, "db-select", "BLOB");
            //         Logger::Instance()->Log(Level::Info, "db-select", "Size of blob: %i", sqlite3_column_bytes(up_stmt.get(), col));
            //         struct tm *blobRetreived;
            //         blobRetreived = (struct tm *) sqlite3_column_blob(up_stmt.get(), col);
            //         Logger::Instance()->Log(Level::Info, "db-select", "Year retrieved from blob: %s", blobRetreived->tm_year+1900zz);
            //         break;
            case SQLITE_NULL:
            {
                row.push_back(SqlUnit(colName));
                break;
            }
            default:
                break;
            }
//            free ((char*)colName);
        }
        result.push_back(row);
    }
    return rows;
}
