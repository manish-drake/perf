#ifndef NAVMODEL_H
#define NAVMODEL_H

#include <QString>
#include <QObject>
#include "scope_timer.h"

class NavModel : public QObject
{
    Q_OBJECT
    scope_timer m_scopeTimer;
public:
    explicit NavModel(QObject *parent = nullptr);    
    Q_INVOKABLE void reset(const QString tag);
    Q_INVOKABLE void scopeDispose();
    Q_INVOKABLE void appLoaded();

signals:
    void onAppLoaded();

};

#endif // NAVMODEL_H
