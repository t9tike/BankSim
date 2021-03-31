#include "siirto.h"
#include "dialogomauimoottorisiirto.h"


/*
Siirto::Siirto()
{
}*/

void Siirto::rajapintafunktioSiirtoOmaUIKomponentti()
{
    //olioDialogOmaUIMoottoriSiirto = new Dialogomauimoottorisiirto;

    olioDialogOmaUIMoottoriSiirto = new Dialogomauimoottorisiirto;
    olioDialogOmaUIMoottoriSiirto->show();
    olioDialogOmaUIMoottoriSiirto->exec();
    delete olioDialogOmaUIMoottoriSiirto;
}
