#ifndef TILITAPAHTUMATMOOTTORIDIALOG_H
#define TILITAPAHTUMATMOOTTORIDIALOG_H

#include <QtSql>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDialog>

namespace Ui {
class TiliTapahtumatMoottoriDialog;
}

class TiliTapahtumatMoottoriDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TiliTapahtumatMoottoriDialog(QWidget *parent = nullptr);
    ~TiliTapahtumatMoottoriDialog();

    void nostojenKirjaaminen();     //hakee nostojen tiedot tietokannasta
    void nostoSummienKirjoittaminenUI(double array[], int arraySize);   //kirjoittaa nostosummat näytölle
    void nostoTilienKirjoittaminenUI(QString array[]);  //kirjoittaa nostojen tilinumerot näytölle

    void laskujenKirjaaminen();     //hakee laskujen tiedot tietokannasta
    void laskujenKirjoittaminenUI(QString laskuttaja[], QString tilinumero_laskuttaja[], double summa_lasku[]); // kirjoittaa laskujen tiedot näytölle

    void siirtojenKirjaaminen();    //hakee siirtojen tiedot tietokannasta
    void siirtoSummanKirjoittaminenUI(double summa_siirto[]); //kirjoittaa siirtosummat näytölle
    void siirtoLahettajanTilinKirjoittaminenUI(QString tilinumeroLahettaja[]);  //kirjoittaa lähettäjien tilit näytölle
    void siirtoVastaanottajanTilinKirjoittaminenUI(QString tilinumeroVastaanottaja[]);  //kirjoittaa vastaanottajien tilit näytölle
    void siirtoViestinKirjoittaminenUI(QString viesti[]);   //kirjoittaa siirrossa lähetetyt viestit näytölle

private slots:
    void on_pushButton_clicked();

private:
    Ui::TiliTapahtumatMoottoriDialog *ui;

};

#endif // TILITAPAHTUMATMOOTTORIDIALOG_H
