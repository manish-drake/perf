#ifndef NAVMODEL_H
#define NAVMODEL_H

#include <QString>
#include <QObject>
#include "scope_memself.h"

class NavModel : public QObject
{
    Q_OBJECT
public:
    explicit NavModel(QObject *parent = nullptr);
    scope_memself *m_scopeMemSelf;
    Q_INVOKABLE void reset(const QString tag);
    Q_INVOKABLE void scopeDispose();

};

#endif // NAVMODEL_H
