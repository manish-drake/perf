#ifndef OBJECTTYPE_H
#define OBJECTTYPE_H

#include "columns.h"
#include "datetime.h"
/*
 * THIS IS AN EXPERIMENTAL CLASS TRYING TO TEST EXTENSIBILITY OF THE API
*/
class ObjectType : public Columns
{
  private:
    schema mSchema;

  public:
    ObjectType(const std::vector<PlatUnit> &columns);
    schema getSchema() const override;
    int Save(const char *table);
};

#endif //OBJECTTYPE_H
