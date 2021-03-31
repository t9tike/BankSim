#include "dllkortinluku.h"
#include <QDebug>

DLLKortinLuku::DLLKortinLuku()
{
}

void DLLKortinLuku::slotPinKoodiOikein() //suoritetaan, kun oikea pin-koodi syötetty
{
    serial->close(); //suljetaan sarjaporttiyhteys
    delete serial;
    delete olioPinKoodiDialog;
    delete olioKortinLukuMoottoriDialog;
    //qDebug() << "dllKortinluku slotissa slotPinKoodiOikein()";
    lahetaSignaaliKirjauduttuSisaan(); //lähetetään signaali pääikkunalle onnistuneesta sisäänkirjautumisesta
}

void DLLKortinLuku::lahetaSignaaliKirjauduttuSisaan() // lähettää signaalin pääikkunalle onnnistuneesta sisäänkirjautumisesta
{
    //qDebug() << "dllKortinluku funktiossa lahetaSignaaliKirjauduttuSisaan()";
    emit signaaliKirjauduttuSisaan();
}

void DLLKortinLuku::rajapintafunktioDLLKortinLuku() //rajapintafunktio
{
    olioKortinLukuMoottoriDialog = new KortinLukuMoottoriDialog;
    olioPinKoodiDialog = new PinKoodiDialog;

    connect(olioPinKoodiDialog, SIGNAL(signaaliPinKoodiOikein()), this, SLOT(slotPinKoodiOikein())); //tehdään signal-slot -yhteys pin-koodin oikeellisuutta varten

    olioKortinLukuMoottoriDialog->show(); // laitetaan moottoridialog näkyväksi

    serial = new QSerialPort(this); // Avataan seuraavilla komennoilla sarjaporttiyhteys RFID-lukijaa varten
    serial->setPortName("com3"); // tässä valitaan, missä portissa lukija on kiinni
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    // serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->setFlowControl(QSerialPort::HardwareControl);

    if (serial->open(QIODevice::ReadWrite))
    {
        qDebug() << serial->portName();
    }else {
        qDebug() << "Portin avaaminen ei onnistunut!";
    }
    connect(serial,SIGNAL(readyRead()),this,SLOT(tulostus())); //tehdään signal-slot -yhteys, jonka avulla suoritetaan slot-funktio kun lukija lukee kortin
}


QString DLLKortinLuku::tulostus() //funktio lukee kortin numeron ja tarkistaa, löytyykö kortin numero tietokannasta
{
    char data[20];
    int bytesread;
    bytesread= serial->read(data,20);
    data[bytesread] = '\0';
    if (bytesread>10) // if-lause tallentaa kortin numeron ja ottaa kortin numerosta ylimääräiset merkit pois
    {
        for (int i=0;i<=9;i++)
        {
            cardSerialNumber = data;
        }
        cardSerialNumber.remove(0, 3);
        cardSerialNumber.remove(10, 3);
        //qDebug() << "Kortin numero: " << cardSerialNumber << endl;
    }
    else
    {
        qDebug()<<"Virhe korttia luettaessa!";
    }


    QSqlQuery query;
    query.exec("SELECT id_kortti FROM Rfid");
    while (query.next()) //while loop tarkistaa, löytyykö kortin numeroa tietokannasta
    {
        QString haettuKortinId = query.value(0).toString();
        //qDebug() << "tietokannasta haettu id_kortti:" << haettuKortinId;
        if(haettuKortinId == cardSerialNumber) //jos kortti löytyy tietokannasta, avataan pin-koodin syöttö
        {
            //qDebug() << "IT'S A MATCH!!";
            olioPinKoodiDialog->show();
            olioPinKoodiDialog->cardSerialNumberTallennus(cardSerialNumber); //lähetetään kortin numero pinkoodidialogille

        }
        else //jos korttia ei ole tietokannassa tai korttia luettaessa tulee virhe, näytetään virheilmoitus
        {
            QMessageBox::critical(nullptr, qApp->tr("Lukuvirhe"),
            qApp->tr("Kortin lukuvirhe. Yritä uudelleen.\n"),
            QMessageBox::Cancel);
        }
    }

    return "palautettavaArvo";
}
