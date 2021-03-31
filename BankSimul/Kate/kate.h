#ifndef KATE_H
#define KATE_H

#include <QtWidgets>
#include "kate_global.h"
#include "dialogomauimoottoridialog.h"

class  Kate
{
private:
    DialogOmaUIMoottoriDialog *olioOmaUIMoottoriDialog;             // Luodaan olio

public:
    void KATESHARED_EXPORT rajapintafunktioDLLOmaUIKomponentti();   // Rajapintafunktio
};

#endif // KATE_H
