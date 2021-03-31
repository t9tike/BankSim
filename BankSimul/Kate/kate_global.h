#ifndef KATE_GLOBAL_H
#define KATE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(KATE_LIBRARY)
#  define KATESHARED_EXPORT Q_DECL_EXPORT
#else
#  define KATESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // KATE_GLOBAL_H
