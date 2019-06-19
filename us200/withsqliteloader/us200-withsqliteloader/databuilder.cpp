#include "databuilder.h"
#include "dbcache.h"
#include "master.h"
#include "navigationcore.h"
#include <QDir>

DataBuilder::DataBuilder()
{

}

int DataBuilder::build() const
{
    QDir dir;
    dir.remove("us200.db");

    DBCache::Select("us","us200.db");

    NavigationCore("Page5","Page2","Page1").Save();
    NavigationCore("Page1","Page3","Page2").Save();
    NavigationCore("Page2","Page4","Page3").Save();
    NavigationCore("Page3","Page5","Page4").Save();
    NavigationCore("Page4","Page1","Page5").Save();

    return 1;
}
