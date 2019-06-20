#include "navigationcore.h"

void NavigationCore::onSetData()
{
    set("prevPath", m_prevPath.toStdString());    
    set("nextPath", m_nextPath.toStdString());
    set("currentPath", m_currentPath.toStdString());
}

void NavigationCore::onGetData(Columns& cols)
{
    m_id = cols.getInt("_ID");
    m_prevPath = QString::fromStdString(cols.getString("prevPath"));
    m_nextPath = QString::fromStdString(cols.getString("nextPath"));
    m_currentPath = QString::fromStdString(cols.getString("currentPath"));
}

schema NavigationCore::getSchema() const
{
    return
    {
        {"prevPath", PLAT_STR},
        {"nextPath", PLAT_STR},
        {"currentPath", PLAT_STR}
    };
}
