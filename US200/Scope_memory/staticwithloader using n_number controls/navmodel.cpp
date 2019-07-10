#include "navmodel.h"

NavModel::NavModel(QObject *parent):
    QObject(parent)
{

}

void NavModel::reset(const QString tag)
{
    std::string str = tag.toStdString();
    const char* p = str.c_str();
    m_scopeMemSelf->Reset(p);
}

void NavModel::scopeDispose()
{
    m_scopeMemSelf->Dispose();
}


