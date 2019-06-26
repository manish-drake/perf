#include "modelbase.h"

ModelBase::ModelBase(QObject *parent) : QAbstractListModel(parent)
{
}

bool ModelBase::setDataByID(const int &ID, const QVariant &value, int role)
{
    int row = getRowIndexByID(ID);
    if(row >= 0){
        QModelIndex idx = index(row);
        return setData(idx, value, role);
    }
    return false;
}

bool ModelBase::removeRowsByID(int row, int count)
{
    if(row >= 0){
        return removeRows(row, count);
    }
    return false;
}

bool ModelBase::isIndexValid(const QModelIndex &index) const
{
    int row = index.row();
    if((row < 0) || (row >= rowCount()) || (!index.isValid())){
        return false;
    } else {
        return true;
    }
}
