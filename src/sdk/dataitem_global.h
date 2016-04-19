#ifndef DATAITEM_GLOBAL_H
#define DATAITEM_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(IOT_EMBEDDED_LIBRARY)
#  define IOT_SHARED_EXPORT Q_DECL_EXPORT
#else
#  define IOT_SHARED_EXPORT Q_DECL_IMPORT
#endif



#endif // DATAITEM_GLOBAL_H
