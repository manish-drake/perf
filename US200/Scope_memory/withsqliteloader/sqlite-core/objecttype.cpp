#include "objecttype.h"
#include "datetime.h"

ObjectType::ObjectType(const std::vector<PlatUnit> &columns)
{
    for (const PlatUnit &pUnit : columns)
    {
        mSchema.insert(std::make_pair(pUnit.Name, pUnit.Tp));
        switch (pUnit.Tp)
        {
        case PLAT_STR:
            set(pUnit.Name, pUnit.TxtVal);
            break;
        case PLAT_DBL:
            set(pUnit.Name, pUnit.DblVal);
            break;
        case PLAT_INT:
            set(pUnit.Name, pUnit.IntVal);
            break;
        case PLAT_BOOL:
            set(pUnit.Name, (int)pUnit.BoolVal);
            break;
        case PLAT_DT:
            set(pUnit.Name, (Datetime)pUnit.DtVal);
        default:
            break;
        }
    }
}

schema ObjectType::getSchema() const
{
    return mSchema;
}
