#ifndef SIIRTO_GLOBAL_H
#define SIIRTO_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SIIRTO_LIBRARY)
#  define SIIRTOSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SIIRTOSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SIIRTO_GLOBAL_H
