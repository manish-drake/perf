#include "navigationmodel.h"
NavigationModel::NavigationModel(QObject *parent):
    ModelBase(parent),
    m_data(PersistableBase::Select_UP(NavigationCore()))
{
}

QString NavigationModel::nextPath(const QString &currPage)
{
    up_catalogue navigation;
     if (DBCache::Current().Get("navigation", navigation))
     {
         auto cats = navigation->Select_UP(apply_filter("currentPath",currPage.toStdString()));
         for(auto &cat:*cats)
         {
         QString name = QString::fromStdString(cat->getString("nextPath"));
         QString path = name + ".qml";         
         return path;
         }
     }
}

QString NavigationModel::prevPath(const QString &currPage)
{
    up_catalogue navigation;
     if (DBCache::Current().Get("navigation", navigation))
     {
         auto cats = navigation->Select_UP(apply_filter("currentPath",currPage.toStdString()));
         for(auto &cat:*cats)
         {
         QString name = QString::fromStdString(cat->getString("prevPath"));
         QString path = name + ".qml";
         return path;
         }
     }
}

int NavigationModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return this->m_data->size();
}

QVariant NavigationModel::data(const QModelIndex &index, int role) const
{
    if(isIndexValid(index)){
        int rowIndex = index.row();
        const NavigationCore &item = *m_data->at(rowIndex);
        switch (role) {
        case Roles::IDRole:
            return item.id();
        case Roles::PrevPathRole:
        case Qt::DisplayRole:
            return item.prevPath();
         case Roles::NextPathRole:
            return item.nextPath();
        default:
            return QVariant();
        }
    } else {
        return QVariant();
    }
}

bool NavigationModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if (row < 0
            || row >= rowCount()
            || count < 0
            || (row + count) > rowCount()) {
        return false;
    }
    beginRemoveRows(parent, row, row + count -1);
    int countLeft = count;
    while (countLeft--) {
        const NavigationCore &item = *m_data->at(row + countLeft);
        PersistableBase::Remove(NavigationCore(), "_ID =" + to_string(item.id()));
    }
    m_data->erase(m_data->begin() + row, m_data->begin() + row + count);
    endRemoveRows();
    return true;
}

QHash<int, QByteArray> NavigationModel::roleNames() const
{
    QHash<int, QByteArray> hash;
    hash.insert(Roles::IDRole, "id");
    hash.insert(Roles::PrevPathRole, "prevPath");
    hash.insert(Roles::NextPathRole, "nextPath");
    return hash;
}

int NavigationModel::getRowIndexByID(const int id) const
{
    int row = -1, idx = 0;
    for(auto &item: *m_data){
        if(item->id() == id)
        {
            row = idx;
            break;
        }
        idx += 1;
    }
    return row;
}

