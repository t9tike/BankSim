#include "nostarahaalib.h"
#include "dialogui.h"



void NostaRahaaLIB::rajaPintafunktio()
{
    yhdistaja = new DialogUI;
    yhdistaja->show();
    yhdistaja->exec();
    delete yhdistaja;

}

NostaRahaaLIB::NostaRahaaLIB()
{

}
 NostaRahaaLIB::~NostaRahaaLIB()
{

}
