#ifndef TABEL_H
#define TABEL_H

#include <utility>
#include <vector>
#include <memory>
#include "db.h"

class Filter;
/**
 * This class is a broker between the front end
 * classes and the DB class that handles core db
 * operations. This class gets data from fron-end
 * classes, formats them using SqlScriptHelper class
 * and passes them to the DB class.
*/
class Table
{
private:
  Table(const char *tableName, const DB &db);
  const char *m_name;
  DB m_db;
  bool m_dropped;
public:
  Table(const char *tableName, const char *dbName);
  bool exists() const;
  int add(const std::vector<DBField> &fields);
  int create(const std::vector<SqlUnit> &values);
  int update(const int &_id, const std::vector<SqlUnit> &sqlUnits);
  int read(sqlResult &results, int limit = 0) const;
  int read(sqlResult &results, const Filter &filter, int limit = 0) const;
  int read(sqlResult &results, const std::string &sqlFilter, int limit = 0) const;
  int read(sqlResult &results, const std::string &sqlFilter, const std::string &sqlSort, int limit = 0) const;
  int read(sqlResult &results, const std::string &joinCondition, const Filter &filter, int limit = 0) const;
  int del(const int &_id) const;
  int del(const std::string &sqlFilter) const;
  int drop();
};

#endif //TABEL_H
