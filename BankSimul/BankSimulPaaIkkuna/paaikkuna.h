#ifndef PAAIKKUNA_H
#define PAAIKKUNA_H

#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QtWidgets>
#include <QtSql>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSerialPort>
#include <QTimer>


#include "connection.h"
#include "C:\BankSimul\DLLKortinLuku\dllkortinluku.h"
#include "C:\BankSimul\DLLTiliTapahtumat\dlltilitapahtumat.h"
#include "C:\BankSimul\Kate\kate.h"
#include "C:\BankSimul\Siirto\siirto.h"
#include "C:\BankSimul\NostaRahaaLIB\nostarahaalib.h"
#include "C:\BankSimul\MaksaLasku_DLL\maksalasku_dll.h"

namespace Ui {
class PaaIkkuna;
}

class PaaIkkuna : public QMainWindow
{
    Q_OBJECT

public:
    explicit PaaIkkuna(QWidget *parent = nullptr);
    virtual ~PaaIkkuna();
    void runDLLKortinLuku(); // Tommin lisäämä, käytetään sovelluksen käynnistyksessä avaamaan kirjautumisikkuna

private slots:

    void slotKirjauduttuSisaan();       // Tommin lisäämä - suoritetaan, kun kirjautuminen on onnistunut

    void slotTimeOut();                 // Suoritetaan, kun timerin aika loppuu

    void on_pushButtonNosto_clicked();

    void on_pushButtonKate_clicked();

    void on_pushButtonLasku_clicked();

    void on_pushButtonSiirto_clicked();

    void on_pushButtonTiliTapahtumat_clicked();

    void on_pushButtonKirjauduUlos_clicked();

private:
    Ui::PaaIkkuna *ui;

    DLLKortinLuku *olioDLLKortinLuku;           //luodaan dll:ien oliot
    DLLTiliTapahtumat *olioDLLTiliTapahtumat;
    Kate *olioKate;
    Siirto *olioSiirto;
    NostaRahaaLIB *olioNostaRahaaLIB;
    MaksaLasku_DLL *olioMaksaLasku_DLL;

    QTimer *ajastin;    //luodaan ajastimelle olio sekä muuttuja, kuinka pitkä ajastimen aika on
    int timeOutAika;

};

#endif // PAAIKKUNA_H
