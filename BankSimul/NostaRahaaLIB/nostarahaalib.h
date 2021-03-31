#ifndef NOSTARAHAALIB_H
#define NOSTARAHAALIB_H

#include "nostarahaalib_global.h"
#include "dialogui.h"
#include <QWidget>
#include <QApplication>


class NOSTARAHAALIBSHARED_EXPORT NostaRahaaLIB: public DialogUI
{

public:
    NostaRahaaLIB();
    ~NostaRahaaLIB();
    void NOSTARAHAALIBSHARED_EXPORT rajaPintafunktio();

private:
    DialogUI *yhdistaja;

};

#endif // NOSTARAHAALIB_H
