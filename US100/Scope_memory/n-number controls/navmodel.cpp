#include "navmodel.h"

NavModel::NavModel(QObject *parent):
    QObject(parent)
{

}

void NavModel::scopeDispose()
{
    m_scopeMemSelf->Dispose();
}


