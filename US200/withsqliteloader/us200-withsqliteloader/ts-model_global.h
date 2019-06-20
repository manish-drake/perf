#ifndef TSMODEL_GLOBAL_H
#define TSMODEL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TSMODEL_LIBRARY)
#  define TSMODELSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TSMODELSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // TSMODEL_GLOBAL_H
