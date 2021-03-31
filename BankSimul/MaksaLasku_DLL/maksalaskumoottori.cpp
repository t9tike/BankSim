#include "maksalaskumoottori.h"
#include "ui_maksalaskumoottori.h"
#include "maksalasku_dll.h"
#include "maksalasku_dll_global.h"



MaksaLaskuMOOTTORI::MaksaLaskuMOOTTORI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MaksaLaskuMOOTTORI)
{
    ui->setupUi(this);
    this->setWindowTitle("Lasku");

    QSqlTableModel *model;              // Heti ohjelman alussa päivitetään maksamattomien laskujen määrä ja tulostetaan se ulos
    model = new QSqlTableModel;
    model->setTable("Lasku");
    model->setFilter("maksun_tila = 1");
    model->select();

    int uusiMaara = model->rowCount();
    ui->labelLASKULKM->setNum(uusiMaara);
    comboPaivitys(uusiMaara);

    delete model;
}

MaksaLaskuMOOTTORI::~MaksaLaskuMOOTTORI()
{
    delete ui;
}

void MaksaLaskuMOOTTORI::on_pushButtonPOISTU_clicked()          // Tässä funktiossa ohjelma suljetaan napin painalluksella
{
    this->close();
}

void MaksaLaskuMOOTTORI::uusiKateDB()                           // Tässä funktiossa tehdään oikeastaan tärkeimmät asiat
{


 QString asiakasTiliNro;

 QSqlQuery etsiKate;
    etsiKate.prepare("SELECT kate FROM Tili WHERE id_tili = :tiliID ");         // Haetaan tili taulusta haluttu kate käyttäne tiliID muuttujaa
    etsiKate.bindValue(":tiliID", tiliID);
    etsiKate.exec();
    while (etsiKate.next())
    {
        tilinKate = etsiKate.value(0).toString();
    }
    qDebug()<<"Tilinkate alunperin :"<< tilinKate<<endl;

    jaljelleJaavaKate = tilinKate.toDouble() - summa_lasku;     // Vähennetään katteesta laskun summa ja tulostetaan ulos uusi kate
    QString jaljelleJaavaKateString = QString::number(jaljelleJaavaKate, 'f', 2);
    ui->labelJAAVAKATE->setText(jaljelleJaavaKateString);
    qDebug()<<"Tilinkate jälkikäteen:"<< jaljelleJaavaKate<<endl;

    QSqlQuery kate;
        kate.prepare("UPDATE  Tili SET Kate  = :uusiKate WHERE id_tili = :tiliID");       // Tili tauluun päivitetään uusi kate
        kate.bindValue(":uusiKate", jaljelleJaavaKate);
        kate.bindValue(":tiliID", tiliID);
        kate.exec();

        QSqlQuery maksunTila;
            maksunTila.prepare("UPDATE Lasku SET maksun_tila  = 0 WHERE id_lasku = :laskuID");       // Kun lasku maksettu niin maskun tila päivitetään maksetuksi
            maksunTila.bindValue(":laskuID", laskuID);
            maksunTila.exec();

            QSqlQuery tilinumero;
                tilinumero.prepare("SELECT tilinumero_asiakas FROM Tili WHERE id_tili = :tiliID");      // Haetaan tilinumero miltä tililtä lasku maksetaan
                tilinumero.bindValue(":tiliID", tiliID);
                tilinumero.exec();
                while (tilinumero.next())
                {
                    asiakasTiliNro = tilinumero.value(0).toString();
                }

            if(asiakasTiliNro == &Kayttotili)                                               // Jos maksettu lasku maksettiin "käyttötililtä" niin kerrotaan se
            {
                ui->labelMikaTili->setText("Käyttötili");
                qDebug()<<"Käyttötilin tilinumero ="<<asiakasTiliNro<<endl;
            }
            else if (asiakasTiliNro == &Saastotili)                                         // Jos maksettu lasku maksettiin "säästötililtä" niin kerrotaan se
            {
                ui->labelMikaTili->setText("Säästötili");
                qDebug()<<"Säästötilin tilinumero ="<<asiakasTiliNro<<endl;
            }

            ui->labelTilinumeroUlosJaava->setText(asiakasTiliNro);

            QMessageBox::information(this,tr("Lasku"),tr("Lasku maksettu!"));                 // Viesti maksetusta laskusta


            QSqlTableModel *refresh;                                        // Laskun maksamisen jälkeen päivitetään lista maksamattomista laskuista
            refresh = new QSqlTableModel;
            refresh->setTable("Lasku");
            refresh->setFilter("maksun_tila = 1");
            refresh->select();
            laskujenMaara = refresh->rowCount();
            ui->labelLASKULKM->setNum(laskujenMaara);

            int nykyinenindex = ui->comboBoxMISTAMAKSETAAN->currentIndex();     // poistetaan vanhat rivit
            ui->comboBoxMISTAMAKSETAAN->removeItem(nykyinenindex);

            delete refresh;
}
void MaksaLaskuMOOTTORI::on_pushButtonMAKSALASKU_clicked()          // Tämän funktion tehtävä on vain totetuttaa napin painallus
{

uusiKateDB();

}

void MaksaLaskuMOOTTORI::comboPaivitys(int uusiMaara)                    // tässä funktiossa haetaan maksamattomat laskut ja päivitetään alasvetolaatikoille uudet rivit
{
        QString laskujenNimet[uusiMaara];

        QSqlTableModel model;
        model.setTable("Lasku");
        model.setFilter("maksun_tila = 1");
        model.select();

        for (int i = 0; i < uusiMaara; ++i)
        {
            QSqlRecord record = model.record(i);
            laskujenNimet[i] = record.value("laskuttaja").toString();
            ui->comboBoxMISTAMAKSETAAN->addItem(laskujenNimet[i]);
        }

}

void MaksaLaskuMOOTTORI::on_comboBoxMISTAMAKSETAAN_currentIndexChanged(const QString &arg1)         // Alasvetolaatikon toiminnallisuus
{
    QString filter = "laskuttaja = ";             // näytetään mikäs lasku siellä onkaan menossa
        filter.append("'");
        filter.append(arg1);
        filter.append("'");
        qDebug() << filter;

        QSqlTableModel model;                      // Etsitään laskun tiedot ja luodaan niille muuttuja
        model.setTable("Lasku");
        model.setFilter(filter);
        model.select();
        QSqlRecord record = model.record(0);
        QString id_tili = record.value("id_tili").toString();
        tiliID = id_tili.toShort();
        QString id_lasku = record.value("id_lasku").toString();
        laskuID = id_lasku.toShort();
        QString tilinumero_laskuttaja = record.value("tilinumero_laskuttaja").toString();
        QString pankki_laskuttaja = record.value("pankki_laskuttaja").toString();
        QString laskuttaja = record.value("laskuttaja").toString();
        laskuttajaUlos = laskuttaja;
        QString viitenumero = record.value("viitenumero").toString();
        summa_lasku = record.value("summa_lasku").toDouble();                  
        QString summa_laskuString = QString::number(summa_lasku, 'f', 2);

        ui->labelLASKuttajaULOS->setText(laskuttaja);                   // tulostetaan laskun tiedot ulos
        ui->labelTilinumeroULOS->setText(tilinumero_laskuttaja);
        ui->labelViitenumeroULOS->setText(viitenumero);
        ui->labelPankkiULOs->setText(pankki_laskuttaja);
        ui->labelSUMMAulos->setText(summa_laskuString);
}






