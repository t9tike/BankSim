#ifndef SIIRTO_H
#define SIIRTO_H

#include "siirto_global.h"
#include "dialogomauimoottorisiirto.h"

#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QtWidgets>
#include <QtSql>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>

class  Siirto
{

public:
    //Siirto();
    void SIIRTOSHARED_EXPORT rajapintafunktioSiirtoOmaUIKomponentti();

private:
    Dialogomauimoottorisiirto *olioDialogOmaUIMoottoriSiirto;
};

#endif // SIIRTO_H
