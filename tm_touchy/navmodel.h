#ifndef NAVMODEL_H
#define NAVMODEL_H

#include <QString>
#include <QObject>
#include "scope_timer.h"

class NavModel : public QObject
{
    Q_OBJECT
    scope_timer m_scopeTimer;

    explicit NavModel(QObject *parent = nullptr);

public:
    static NavModel* m_singleton;
    static NavModel& Instance()
    {
        if(!m_singleton)
        {
            m_singleton = new NavModel();
        }
        return *m_singleton;
    }
    Q_INVOKABLE void reset(const QString tag);
    Q_INVOKABLE void scopeDispose();
    Q_INVOKABLE void appLoaded();

signals:
    void onAppLoaded();
};

#endif // NAVMODEL_H
