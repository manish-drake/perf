#ifndef MODELBASE_H
#define MODELBASE_H

#include <vector>
#include <memory>
#include <QObject>
#include <QAbstractListModel>

class ModelBase : public QAbstractListModel
{
public:
    explicit ModelBase(QObject *parent = 0);

protected:
    virtual int getRowIndexByID(const int id) const = 0;
    bool setDataByID(const int &ID, const QVariant &value, int role);
    bool removeRowsByID(int row, int count);
    bool isIndexValid(const QModelIndex &index) const;
};

#endif // MODELBASE_H
