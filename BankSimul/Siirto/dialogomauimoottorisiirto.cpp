#include "dialogomauimoottorisiirto.h"
#include "ui_dialogomauimoottorisiirto.h"
#include "siirto.h"

Dialogomauimoottorisiirto::Dialogomauimoottorisiirto(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogomauimoottorisiirto)
{
    ui->setupUi(this);
    this->setWindowTitle("Siirto");
}

Dialogomauimoottorisiirto::~Dialogomauimoottorisiirto()
{
    delete ui;
}

void Dialogomauimoottorisiirto::on_pushButtonSuljeSiirto_clicked()
{
    this->close();
}

void Dialogomauimoottorisiirto::on_pushButtonPaivita_clicked()
{
    QSqlTableModel *model;                                              // luodaan QSql model
    model = new QSqlTableModel;
    model->setTable("Tilisiirto");                                      // valitaan Tilisiirtotaulu
    model->select();
    ID_Nosto = model->rowCount() + 1;

       nostettavaSumma = ui->lineEditSiirrettavaSumma->text().toDouble();   // nostettavasummamuuttuja on lineedittiin syötetty summa muutettuna doubleksi
       viesti = ui->lineEditViestiVastaanottajalle->text();                 // QString viesti on lineedittiin syötetty teksti
                                                                            // alla kasa ehtoja
       if   (kytkin2 == 1 || kytkin2 ==2)                                   // jos valintalaatikko2 on tilinumero1 tai 2
       {
           if  (ui->lineEditMuunnettaTilinumero->text()!= "")               // ja lineedit tilinumero ei ole tyhjä
           {
               QMessageBox::critical(this,tr("Virhe"),tr("Virhe, vastaanottajana voi olla vain 1 tilinumero")); //ilmoittaa virheestä
               return;
           }
       }

       else if  (kytkin2 == 3 && ui->lineEditMuunnettaTilinumero->text() == "") // jos lineedit tilinumero on tyhjä ja vastaanottajan vetolaatikko on tyhjä
       {
           QMessageBox::critical(this,tr("Virhe"),tr("Virhe, valitse vastaanottaja"));
           //qDebug()<<"Virhe, valitse vastaanottaja" << endl;
           return;
       }

       if   (kytkin1 == 3)                                                      // tarkistetaan onko lähettäjän tiliä valittu
       {
           QMessageBox::critical(this,tr("Virhe"),tr("Virhe, syötä tilinumero"));
           //qDebug()<<"Virhe, syötä tilinumero" << endl;
           return;
       }

       if   (ui->lineEditMuunnettaTilinumero->text()!= "")                  // jos kirjoitettava tilinumero lineeditissä muu kuin tyhjä
       {                                                                    // niin tilinumero on lineedittiin kirjoitettu
            tilinumero= ui->lineEditMuunnettaTilinumero->text();
       }

       //qDebug()<<nostettavaSumma<<endl;

       if   (kytkin1 ==1 && kytkin2 ==1)                                    // tarkistetaan ettei tilinumerot vetolaatikoissa ole samat
       {
           QMessageBox::critical(this,tr("Virhe"),tr("Virhe, sama tilinumero"));
           //qDebug()<<"samalta tililta menossa" << endl;
           return;
       }
       else if  (kytkin1 ==2 && kytkin2 ==2)
       {
           QMessageBox::critical(this,tr("Virhe"),tr("Virhe, sama tilinumero"));
           //qDebug()<<"samalta tililta menossa" << endl;
           return;
       }

       if   (ui->lineEditSiirrettavaSumma->text()== "" || nostettavaSumma <= 0)                     // tarkistetaan onko laitetu lähetettävää summaa
       {
           QMessageBox::critical(this,tr("Virhe"),tr("Virhe, syötä siirrettävä summa"));
           //qDebug()<<"Virhe, syötä tilinumero" << endl;
           return;
       }

       vahennusLasku();                                                          // kutsutaan funktioita
       yhteenLasku();
       tulostaUusiKate();
       ekaTilinKate();
       tokaTilinKate();
       ui->labelSiirrettavaKate->clear();
       ui->labelVastaanottajanKate->clear();

       QMessageBox::information(this,tr("Siirto"),tr("Siirto onnistui!"));
}

void Dialogomauimoottorisiirto::ekaTilinKate()                               // hakee tilin id_tili = 1 katteen
{
    QSqlQuery query;
        query.exec("SELECT kate FROM Tili WHERE id_tili = 1");
        while (query.next())
        {
            double tilinKateDouble = query.value(0).toDouble();                  //tilinkatedouble on queryn tulos
            QString tilinKate = QString::number(tilinKateDouble, 'f', 2);               // stringi tilinkate on queryn tulos joka muutetaan stringiksi
            ui->labelSiirrettavaKate->setText("Kate: " + tilinKate);                   // asettaa stringi tilinkatteen labelsiirrettävään katteeseen
        }
}

void Dialogomauimoottorisiirto::tokaTilinKate()
{
    QSqlQuery query;
        query.exec("SELECT kate FROM Tili WHERE id_tili = 2");
        while (query.next())
        {
            double tilinKateDouble = query.value(0).toDouble();
            QString tilinKate2 = QString::number(tilinKateDouble, 'f', 2);
            ui->labelSiirrettavaKate->setText("Kate: " + tilinKate2);
        }
}

void Dialogomauimoottorisiirto::kolmannenTilinKate()
{
    QSqlQuery query;
        query.exec("SELECT kate FROM Tili WHERE id_tili = 1");
        while (query.next())
        {
            double tilinKateDouble = query.value(0).toDouble();
            QString tilinKate = QString::number(tilinKateDouble, 'f', 2);
            ui->labelVastaanottajanKate->setText("Kate: " + tilinKate);
        }
}

void Dialogomauimoottorisiirto::neljannenTilinKate()
{
    QSqlQuery query;
        query.exec("SELECT kate FROM Tili WHERE id_tili = 2");
        while (query.next())
        {
            double tilinKateDouble = query.value(0).toDouble();
            QString tilinKate2 = QString::number(tilinKateDouble, 'f', 2);
            ui->labelVastaanottajanKate->setText("Kate: " + tilinKate2);
        }
}

void Dialogomauimoottorisiirto::vahennusLasku()                              // hakee uuden katteen
{
        QSqlQuery query1;                                               // luo queryn
        query1.prepare("SELECT Kate FROM Tili WHERE id_tili = :tiliID");  // valmistelee hakemaan tietoja Tilitaulusta kate kohdasta, id_tili vastaa tiliID muuttujaa
        query1.bindValue(":tiliID", tiliID);                              // sidotaan tiliID vastaamaan muuttujaa tiliID, muuttujaa käyttäessä käytä :
            query1.exec();
            while (query1.next())
            {
                 tilinKate = query1.value(0).toDouble();
            }

            tulevaKate = tilinKate-nostettavaSumma;                         // lasketaan tulevakate
            //qDebug()<<tulevaKate<<endl;
            //uusikate2 = QString::number(tulevaKate);                        // muutetaan stringiksi
            ui->labelSiirrettavaKate->setText(uusikate2);
}

void Dialogomauimoottorisiirto::yhteenLasku()
{
        QSqlQuery query1;
        query1.prepare("SELECT Kate FROM Tili WHERE id_tili = :tiliID2");
        query1.bindValue(":tiliID2", tiliID2);
            query1.exec();
            while (query1.next())
            {
                 tilinKate = query1.value(0).toDouble();
            }
            kate = nostettavaSumma+tilinKate;               // kate on nostettava plus tilinkate
            //uusikate3 = QString::number(kate);
            //qDebug() <<nostettavaSumma+tilinKate<<endl;
}

void Dialogomauimoottorisiirto::tulostaUusiKate()
{
        QSqlQuery query2;
           query2.prepare("INSERT INTO Tilisiirto VALUES(:ID_nosto, :tiliID, :tili, :summaNosto, :viesti)");        //Nosto tauluun lisätään uusi rivi
           query2.bindValue(":summaNosto", nostettavaSumma);                                                        // sidotaan lisättävät arvot vastaamaan haluttuja muuttujia
           query2.bindValue(":tiliID", tiliID);
           query2.bindValue(":tili", tilinumero);
           query2.bindValue(":ID_nosto", ID_Nosto);
           query2.bindValue(":viesti", viesti);
           query2.exec();

        QSqlQuery Query3;
            Query3.prepare("UPDATE  Tili SET Kate  = :uusiKate WHERE id_tili = :tiliID");       // Tili tauluun päivitetään vähennettyä katetta
            Query3.bindValue(":uusiKate", tulevaKate);
            Query3.bindValue(":tiliID", tiliID);
            Query3.exec();

        QSqlQuery Query4;
            Query4.prepare("UPDATE  Tili SET Kate  = :uusiKate WHERE id_tili = :tiliID2");       // Tili tauluun päivitetään lisättyä katetta
            Query4.bindValue(":uusiKate",  kate);
            Query4.bindValue(":tiliID2", tiliID2);
            Query4.exec();
            if(!Query4.exec()) {
            qDebug() << "Siirto toiselle tilille epaonnistui" << Query4.lastError();
            }
}

void Dialogomauimoottorisiirto::on_comboBoxMista_currentIndexChanged(const QString &arg1)       // vetolaatikon valintoja
{                                                                                               // saldon näyttämiseen ohjelmassa, funktioihin
        if  (arg1 == ui->comboBoxMista->itemText(0))
        {
            kytkin1 = 3;
            ui->labelSiirrettavaKate->clear();
        }

        else if (arg1 == ui->comboBoxMista->itemText(1))
        {
           tiliID = 1;
           ekaTilinKate();
           kytkin1 = 1;
        }
        else if (arg1 == ui->comboBoxMista->itemText(2))
        {
            tiliID = 2;
            tokaTilinKate();
            kytkin1 = 2;
        }
}

void Dialogomauimoottorisiirto::on_comboBoxMihin_currentIndexChanged(const QString &arg1)
{
    if (arg1 == ui->comboBoxMihin->itemText(0))
        {
           kytkin2 = 3;
           ui->labelVastaanottajanKate->clear();
        }

    else if (arg1 == ui->comboBoxMihin->itemText(1))
        {
           tiliID2 = 1;
           tilinumero = "FI1234567891234567";
           kytkin2 = 1;
           kolmannenTilinKate();
        }
    else if (arg1 == ui->comboBoxMihin->itemText(2))
        {
            tiliID2 = 2;
            tilinumero = "FI9988776655443322";
            kytkin2 = 2;
            neljannenTilinKate();
        }
}
