#ifndef NAVIGATIONMODEL_H
#define NAVIGATIONMODEL_H

#include "navigationcore.h"
#include <QQmlPropertyMap>
#include "dbcache.h"
#include "modelbase.h"
#include "ts-model_global.h"
#include "scope_timer.h"

class TSMODELSHARED_EXPORT NavigationModel : public ModelBase
{
    Q_OBJECT
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool removeRows(int row, int count, const QModelIndex& parent) override;
    QHash<int, QByteArray> roleNames() const override;
    int getRowIndexByID(const int id) const override;
    enum Roles {
        IDRole = Qt::UserRole +1,
        PrevPathRole,
        NextPathRole
    };
    std::unique_ptr<std::vector<std::unique_ptr<NavigationCore>>> m_data;
    scope_timer m_scopeTimer;
public:
    NavigationModel(QObject *parent = 0);
    Q_INVOKABLE QString nextPath(const QString &currPage);
    Q_INVOKABLE QString prevPath(const QString &currPage);
    Q_INVOKABLE void scopeDispose();
    Q_INVOKABLE void appLoaded();

signals:
    void onAppLoaded();
};

#endif // NAVIGATIONMODEL_H
