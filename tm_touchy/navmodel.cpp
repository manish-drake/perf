#include "navmodel.h"

NavModel* NavModel::m_singleton = nullptr;

NavModel::NavModel(QObject *parent):
    QObject(parent)
{

}

void NavModel::reset(const QString tag)
{
    std::string str = tag.toStdString();
    const char* p = str.c_str();
    m_scopeTimer.Reset(p);
}

void NavModel::scopeDispose()
{
    m_scopeTimer.Dispose();
}

void NavModel::appLoaded()
{
    emit onAppLoaded();
}
