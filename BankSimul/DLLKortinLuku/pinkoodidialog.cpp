#include "pinkoodidialog.h"
#include "ui_pinkoodidialog.h"

PinKoodiDialog::PinKoodiDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PinKoodiDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Pin");
}

PinKoodiDialog::~PinKoodiDialog()
{
    delete ui;
}

void PinKoodiDialog::on_pushButtonOk_clicked()
{
    QString haettuPin; //tähän tallenetaan tietokannasta haettu pin
    QString syotettyPin = ui->lineEditPinSyotto->text(); // tähän tallenetaan käyttäjän syöttämä pin
    //qDebug() << syotettyPin;
    //qDebug() << cardSerialNumber;

    QSqlQuery query; 
    query.prepare("SELECT pin_kortti FROM Rfid WHERE id_kortti = :cardSerial"); //valitaan Rfid-taulusta pin_kortti, joka kuuluu luetulle kortille
    query.bindValue(":cardSerial", cardSerialNumber);
    query.exec();

    while (query.next()) //while-loop tarkastaa, onko pin-koodi syötetty oikein tälle luetulle kortille
    {
        haettuPin = query.value(0).toString();
        //qDebug() << "tietokannasta haettu pin:" << haettuPin; // haetaan tietokannasta kortille kuuluva pin
        if(haettuPin == syotettyPin) // jos syötetty pin ja tietokannasta haettu pin on oikein, lähetetään signaali dllkortinluvulle
        {
            //qDebug() << "PIN OIKEIN!";
            emit signaaliPinKoodiOikein();
        }
        else //jos pin on väärin, pyydetään käyttäjää yrittämään uudestaan
        {
            QMessageBox::critical(nullptr, qApp->tr("Väärä PIN"),
            qApp->tr("Väärä PIN-koodi. Yritä uudelleen.\n"),
            QMessageBox::Ok);
        }
    }

}

void PinKoodiDialog::cardSerialNumberTallennus(QString lahetettySerial) //tallennetaan dllkortinluvun lähettämä kortin numero sekä kirjoitetaan asiakkaan nimi näytölle
{
    cardSerialNumber = lahetettySerial;
    QString etunimi = "";
    QString sukunimi = "";
    short id_asiakas = 0;

    QSqlQuery query;
    query.prepare("SELECT id_asiakas FROM Rfid WHERE id_kortti = :cardSerial"); //haetaan id_asiakas kortin numeron avulla
    query.bindValue(":cardSerial", cardSerialNumber);
    query.exec();
    while (query.next()) //tallenetaan asiakkaan id
    {
        id_asiakas = query.value(0).toInt();
        //qDebug() << "tietokannasta haettu id_asiakas:" << id_asiakas;
    }

    query.prepare("SELECT etunimi FROM Asiakas WHERE id_asiakas = :asiakasid"); //tallennetaan asiakkaan etunimi
    query.bindValue(":asiakasid", id_asiakas);
    query.exec();
    while (query.next())
    {
        etunimi = query.value(0).toString();
        //qDebug() << "tietokannasta haettu etunimi:" << etunimi;
    }


    query.prepare("SELECT sukunimi FROM Asiakas WHERE id_asiakas = :asiakasid"); //tallennetaan asiakkaan sukunimi
    query.bindValue(":asiakasid", id_asiakas);
    query.exec();
    while (query.next())
    {
        sukunimi = query.value(0).toString();
        //qDebug() << "tietokannasta haettu sukunimi:" << sukunimi;
    }

    etunimi.append(" ");
    ui->labelHaettuNimi->setText(etunimi.append(sukunimi)); //kirjoitetaan asiakkaan nimi näytölle
    //qDebug() << "funktion cardSerialNumberTallennus funktion loppu" << etunimi;

}

void PinKoodiDialog::on_pushButtonKeskeyta_clicked()
{
    ui->lineEditPinSyotto->setText(""); //tyhjennetään pin-syötön line-edit jos kirjautuminen keskeytetään
    this->close();
}
