#include "dialogui.h"
#include "ui_dialogui.h"
#include "nostarahaalib.h"


DialogUI::DialogUI(QWidget *parent) :           // TÄSSÄ FUNKTIOSSA NOSTETAAN HETI ESIIN TUILINUMERO JA TILIN KATE KUN OHJELMA AVATAAN
    QDialog(parent),
    ui(new Ui::DialogUI)
{
    ui->setupUi(this);
    this->setWindowTitle("Nosto");
    tiliNumero1();
    tiliNumero2();
    naytaKateT1();
    naytaKateT2();
}

DialogUI::~DialogUI()
{
        delete ui;

}

void DialogUI::on_NAPPIJOU_clicked()        // TÄSSÄ FUNKTIOSSA TAIKA TAPAHTUU, KUN NOSTA NAPPIA PAINETAAN NIIN ASIAT ALKAA RULLAAN
{

        QSqlTableModel *model;              // Varmistetaan että Nosto taulun Primary Key on joka rivillä yhdellä nouseva
        model = new QSqlTableModel;
        model->setTable("Nosto");
        model->select();
        ID_Nosto = model->rowCount() +1;

        if ( kytkin == 1)                   // varmistetaan että tili on valittu ennen noston suorittamista
        {
            QMessageBox::critical(this,tr("Virhe"),tr("Virhe, valitse tili miltä rahat nostetaan!"));
            return;
        }

       nostettavaSumma = ui->lineEditVAlitseSUmma->text().toDouble();  // Nostettava summa otetaan LineEditistä kiinni muuttujaan

       if(nostettavaSumma <= 0 || ui->lineEditVAlitseSUmma->text() == "")
       {
           QMessageBox::critical(this,tr("Virhe"),tr("Virheellinen nostosumma"));
           return;
       }
       else
       {
           qDebug()<<nostettavaSumma<<endl;

           uusiKate();
           tulostaUusiKate();
           naytaKateT1();
           naytaKateT2();

           QMessageBox::information(this,tr("Nosto"),tr("Rahat tulossa!"));         // Ilmoitetaan rahojan tulosta!
       }

       delete model;

}

void DialogUI::tiliNumero1()            // TÄSSÄ FUNKTIOSSA ETSITÄÄN TILINUMERO 1 TILI TAULUSTA JA KIRJOITETAAN SE TILI SARAKKEESEEN NÄYTÖLLE
{
    QSqlQuery query;
        query.exec("SELECT tilinumero_asiakas FROM Tili WHERE id_tili = 1");
        while (query.next())
        {
            QString asiakasTiliNro1 = query.value(0).toString();
            ui->lineEdittiliNumero1->setText(asiakasTiliNro1);
        }


}
void DialogUI::tiliNumero2()            // TÄSSÄ FUNKTIOSSA ETSITÄÄN TILINUMERO 2 TILI TAULUSTA JA KIRJOITETAAN SE TILI SARAKKEESEEN NÄYTÖLLE
{
    QSqlQuery query;
        query.exec("SELECT tilinumero_asiakas FROM Tili WHERE id_tili = 2");
        while (query.next())
        {
            QString asiakasTiliNro2 = query.value(0).toString();
            ui->lineEditTiliNumero2->setText(asiakasTiliNro2);
        }

}


void DialogUI::naytaKateT1()      // TÄSSÄ FUNKTIOSSA ETSITÄÄN KATE TILIN 1 TAULUSTA JA NÄYTETÄÄN SE KATE SARAKKEESSA
{
    QSqlQuery query;
        query.exec("SELECT kate FROM Tili WHERE id_tili = 1");
        while (query.next())
        {
            //QString tilinKate = query.value(0).toString();
            double tilinKateDouble = query.value(0).toDouble();
            QString tilinKate = QString::number(tilinKateDouble, 'f', 2);
            ui->lineEditKATE->setText(tilinKate);
        }
}
void DialogUI::naytaKateT2()        // TÄSSÄ FUNKTIOSSA ETSITÄÄN KATE TILIN 2 TAULUSTA JA NÄYTETÄÄN SE KATE SARAKKEESSA
{
    QSqlQuery query;
        query.exec("SELECT kate FROM Tili WHERE id_tili = 2");
        while (query.next())
        {
            //QString tilinKate2 = query.value(0).toString();
            double tilinKateDouble = query.value(0).toDouble();
            QString tilinKate2 = QString::number(tilinKateDouble, 'f', 2);
            ui->lineEditKATE2->setText(tilinKate2);
        }
}

void DialogUI::uusiKate()               // TÄSSÄ FUNKTIOSSA ETSITÄÄN KATE TILI TAULUSTA JA KIRJOITETAAN VÄHENNYKSEN JÄLKEEN UUSI KATE NÄYTÖLLE
{
        QSqlQuery query1;
        query1.prepare("SELECT kate FROM Tili WHERE id_tili = :mikaTili");
        query1.bindValue(":mikaTili", tilinKate);
            query1.exec();
            while (query1.next())
            {
                 tilinKate = query1.value(0).toDouble();
            }

           tulevaKate = tilinKate-nostettavaSumma;
           qDebug()<<tulevaKate<<endl;
           uusikate = QString::number(tulevaKate, 'f', 2);
           ui->lineEditUusiKate->setText(uusikate);

}

void DialogUI::tulostaUusiKate()        // TÄSSÄ FUNKTIOSSA KIRJOITETAAN NOSTOTAPAHTUMA NOSTO TAULUUN SEKÄ PÄIVITETÄÄN TILI TAULU
{
       QSqlQuery query2;
           query2.prepare("INSERT INTO Nosto VALUES(:ID_nosto, :tiliID, :summaNosto)");        //Nosto tauluun lisätään uusi rivi
           query2.bindValue(":summaNosto", nostettavaSumma);
           query2.bindValue(":tiliID", tiliID);
           query2.bindValue(":ID_nosto", ID_Nosto);
           query2.exec();

        QSqlQuery Query3;
            Query3.prepare("UPDATE  Tili SET Kate  = :uusiKate WHERE id_tili = :tiliID");       // Tili tauluun päivitetään tili taulua
            Query3.bindValue(":uusiKate", uusikate);
            Query3.bindValue(":tiliID", tiliID);
            Query3.exec();
}


void DialogUI::on_pushButtonPOISTU_clicked()            // TÄSSÄ FUNKTIOSSA POISTUTAAN OHJELMASTA KUN POISTU NAPPIA ON PAINETTU
{
    this->close();

}

void DialogUI::on_comboBoxTilinValinta_currentIndexChanged(const QString &arg1)     // TÄSSÄ FUNKTIOSSA VALITAAN TILI MILTÄ RAHAT NOSTETAAN
{
    if (arg1 == ui->comboBoxTilinValinta->itemText(0))              // Jos tiliä ei ole valittu, popup ikkunassa ilmoitetaan siittä
    {
        kytkin =1;
    }

    else if (arg1 == ui->comboBoxTilinValinta->itemText(1))         // Jos valitaan tili 1 niin päivitetään muuttujat ja käytetään tiettyjäfunktioita
    {
       kytkin =2;
       tiliID = 1;
       tilinKate = 1;
       tiliNumero1();
       naytaKateT1();
    }

    else if (arg1 == ui->comboBoxTilinValinta->itemText(2))         // Jos valitaan tili 2 niin päivitetään muuttujat ja käytetään tiettyjäfunktioita
    {
        kytkin =2;
        tilinKate = 2;
        tiliID = 2;
        tiliNumero2();
        naytaKateT2();

     }
}
