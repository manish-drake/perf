#ifndef NAVIGATIONCORE_H
#define NAVIGATIONCORE_H

#include "persistablebase.h"
#include <QString>

class NavigationCore :public PersistableBase
{
public:
    explicit NavigationCore(const QString &prevPath, const QString &nextPath, const QString &currentPath);
    NavigationCore();

    schema getSchema() const override;  //to define schema
    void onSetData() override;            //to get data from object into db
    void onGetData(Columns& col) override;   //to get data from db into object

    int id() const;
    void setId(int id);

    QString prevPath() const;
    void setPrevPath(const QString &prevPath);

    QString currentPath() const;
    void setCurrentPath(const QString &currentPath);

    QString nextPath() const;
    void setNextPath(const QString &nextPath);

private:
    int m_id = 0;
    QString m_prevPath;
    QString m_currentPath;
    QString m_nextPath;
};

#endif // NAVIGATIONCORE_H
