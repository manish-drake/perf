#include "navmodel.h"

NavModel::NavModel(QObject *parent):
    QObject(parent)
{

}

void NavModel::scopeDispose()
{
    m_scopeTimer.Dispose();
}

void NavModel::appLoaded()
{
    emit onAppLoaded();
}
