#include "navigationcore.h"

NavigationCore::NavigationCore(const QString &prevPath, const QString &nextPath, const QString &currentPath) :
    PersistableBase("us200.db", "navigation"),
    m_id{0},
    m_prevPath{prevPath},
    m_currentPath{currentPath},
    m_nextPath{nextPath}
{

}

NavigationCore::NavigationCore() : PersistableBase("us200.db", "navigation")
{

}

int NavigationCore::id() const
{
    return _ID();
}

void NavigationCore::setId(int id)
{
    m_id = id;
}

QString NavigationCore::prevPath() const
{
    return m_prevPath;
}

void NavigationCore::setPrevPath(const QString &prevPath)
{
     m_prevPath = prevPath;
}

QString NavigationCore::currentPath() const
{
    return m_currentPath;
}

void NavigationCore::setCurrentPath(const QString &currentPath)
{
     m_currentPath = currentPath;
}

QString NavigationCore::nextPath() const
{
    return m_nextPath;
}

void NavigationCore::setNextPath(const QString &nextPath)
{
    m_nextPath = nextPath;
}


