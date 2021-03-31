#ifndef DLLKORTINLUKU_H
#define DLLKORTINLUKU_H

#include "dllkortinluku_global.h"
#include "kortinlukumoottoridialog.h"
#include "pinkoodidialog.h"

#include <QtSql>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSerialPort>
#include <QObject>

class DLLKORTINLUKUSHARED_EXPORT DLLKortinLuku : public QObject
{
    Q_OBJECT

public:

    DLLKortinLuku();
    void DLLKORTINLUKUSHARED_EXPORT rajapintafunktioDLLKortinLuku(); //rajapintafunktio
    void lahetaSignaaliKirjauduttuSisaan(); //lähettää signaalin pääikkunalle onnistuneesta kirjautumisesta

private:

    KortinLukuMoottoriDialog *olioKortinLukuMoottoriDialog;
    PinKoodiDialog *olioPinKoodiDialog;

    QString palautettavaArvo;
    QSerialPort *serial;
    QString cardSerialNumber;

signals:

    void DLLKORTINLUKUSHARED_EXPORT signaaliKirjauduttuSisaan(); //signaali pääikkunalle onnistuneesta kirjautumisesta

public slots:

    void DLLKORTINLUKUSHARED_EXPORT slotPinKoodiOikein();
    QString DLLKORTINLUKUSHARED_EXPORT tulostus();
};

#endif // DLLKORTINLUKU_H
