#include "dialogomauimoottoridialog.h"
#include "ui_dialogomauimoottoridialog.h"
#include "kate.h"


DialogOmaUIMoottoriDialog::DialogOmaUIMoottoriDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogOmaUIMoottoriDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Kate");
    on_pushButtonSiirraTekstia_clicked();
}

DialogOmaUIMoottoriDialog::~DialogOmaUIMoottoriDialog()
{
    delete ui;
}

void DialogOmaUIMoottoriDialog::on_pushButtonSuljeKate_clicked()
{
    this->close();
}

void DialogOmaUIMoottoriDialog::on_pushButtonSiirraTekstia_clicked()
{
    if  (katePaivitys != true)
    {
        QMessageBox msgBox;                                         // Ilmoittaa tietojen päivityksestä
        msgBox.setText("Katetiedot päivitetty!");
        msgBox.exec();
    }

    QSqlQuery query;
        query.exec("SELECT kate FROM Tili WHERE id_tili = 1");  // Luodaan query ja haetaan katetiedot tililtä
        while (query.next())                                    // Käy kaikki rivit läpi QSqlQueryn funktiolla
        {
            //QString haeKate = query.value(0).toString();        // Luodaan string haeKate joka on queryn arvo
            double haeKateDouble = query.value(0).toDouble();
            QString haeKate = QString::number(haeKateDouble, 'f', 2);
            ui->labelTekstia->setText(haeKate);
        }

    QSqlQuery query2;
        query.exec("SELECT kate FROM Tili WHERE id_tili = 2");
        while (query.next())
        {
            //QString haeKate2 = query.value(0).toString();
            double haeKate2Double = query.value(0).toDouble();
            QString haeKate2 = QString::number(haeKate2Double, 'f', 2);
            ui->labelTekstia2->setText(haeKate2);
        }

    QSqlQuery tilinumero;
        tilinumero.exec("SELECT tilinumero_asiakas FROM Tili WHERE id_tili = 1");
        while   (tilinumero.next())
        {
            QString haetilinro = tilinumero.value(0).toString();
            ui->labelTilinumero_2->setText(haetilinro);
        }

    QSqlQuery tilinumero2;
        tilinumero2.exec("SELECT tilinumero_asiakas FROM Tili WHERE id_tili = 2");
        while   (tilinumero2.next())
        {
            QString haetilinro = tilinumero2.value(0).toString();
            ui->labelTilinumero_3->setText(haetilinro);
        }

    QSqlQuery pankinnimi;
        pankinnimi.exec("SELECT pankki FROM Tili WHERE id_tili = 1");
        while   (pankinnimi.next())
        {
            QString haePankinNimi = pankinnimi.value(0).toString();
            ui->labelPankki->setText(haePankinNimi);
        }

    QSqlQuery pankinnimi2;
        pankinnimi2.exec("SELECT pankki FROM Tili WHERE id_tili = 2");
        while   (pankinnimi2.next())
        {
            QString haePankinNimi2 = pankinnimi2.value(0).toString();
            ui->labelPankki2->setText(haePankinNimi2);
        }

        katePaivitys = 0;
}
