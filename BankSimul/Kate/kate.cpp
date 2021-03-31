#include "kate.h"
#include "dialogomauimoottoridialog.h"

#include <QWidget>
#include <QApplication>
#include <QtWidgets>
#include <QDebug>

void Kate::rajapintafunktioDLLOmaUIKomponentti()
{
    qDebug()<< "ollaan katteen rajapintafunktion alussa" << endl;

    olioOmaUIMoottoriDialog = new DialogOmaUIMoottoriDialog;
    olioOmaUIMoottoriDialog->show();

    olioOmaUIMoottoriDialog->exec();
    delete olioOmaUIMoottoriDialog;
}

