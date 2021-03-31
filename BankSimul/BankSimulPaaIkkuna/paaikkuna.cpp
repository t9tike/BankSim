#include "paaikkuna.h"
#include "ui_paaikkuna.h"
#include "connection.h"

PaaIkkuna::PaaIkkuna(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PaaIkkuna)
{
    ui->setupUi(this);
    this->setWindowTitle("BankSimul");

    olioDLLTiliTapahtumat = new DLLTiliTapahtumat;
    olioDLLKortinLuku = new DLLKortinLuku;
    olioKate = new Kate;
    olioSiirto = new Siirto;
    olioNostaRahaaLIB = new NostaRahaaLIB;
    olioMaksaLasku_DLL = new MaksaLasku_DLL;

    ajastin = new QTimer;
    timeOutAika = 30000; //määritetään aika, minkä ajan kuluttua ohjelma kirjaa käyttäjän automaattisesti ulos

    this->connect(olioDLLKortinLuku, SIGNAL(signaaliKirjauduttuSisaan()), this, SLOT(slotKirjauduttuSisaan()));   //Luo signal-slot -yhteyden onnistuneeseen kirjautumiseen
    this->connect(ajastin, SIGNAL(timeout()), this, SLOT(slotTimeOut())); //luo sifnal-slot-yhteyden ajastimeen
}

PaaIkkuna::~PaaIkkuna()
{
    delete ui;
    delete olioDLLTiliTapahtumat;
    delete olioDLLKortinLuku;
    delete olioKate;
    delete olioSiirto;
    delete olioNostaRahaaLIB;
    delete olioMaksaLasku_DLL;
    delete ajastin;
}

void PaaIkkuna::runDLLKortinLuku() //Suoritetaan ohjelman käynnistyessä
{
    ajastin->stop();
    olioDLLKortinLuku->rajapintafunktioDLLKortinLuku();
}

void PaaIkkuna::slotKirjauduttuSisaan()     //Suoritetaan, kun kirjautuminen on onnistunut
{
    ajastin->start(timeOutAika);
    qDebug() << "slotissa slotKirjauduttuSisaan";
}

void PaaIkkuna::slotTimeOut()   //Suoritetaan, kun ajastimesta on aika loppunut
{
    ajastin->stop();
    olioDLLKortinLuku->rajapintafunktioDLLKortinLuku();
}

void PaaIkkuna::on_pushButtonNosto_clicked()
{
    ajastin->stop();    //pysäytetään ajastin
    olioNostaRahaaLIB->rajaPintafunktio();  //suoritetaan dll
    ajastin->start(timeOutAika);    //kun dll-komponentin ikkuna suljetaan, ajastin alkaa alusta
}

void PaaIkkuna::on_pushButtonKate_clicked()
{
    ajastin->stop();
    olioKate->rajapintafunktioDLLOmaUIKomponentti();
    ajastin->start(timeOutAika);
}

void PaaIkkuna::on_pushButtonLasku_clicked()
{
    ajastin->stop();
    olioMaksaLasku_DLL->RajapintafunktioML();
    ajastin->start(timeOutAika);
}

void PaaIkkuna::on_pushButtonSiirto_clicked()
{
    ajastin->stop();
    olioSiirto->rajapintafunktioSiirtoOmaUIKomponentti();
    ajastin->start(timeOutAika);
}

void PaaIkkuna::on_pushButtonTiliTapahtumat_clicked()
{
    ajastin->stop();
    olioDLLTiliTapahtumat->rajapintafunktioDLLTiliTapahtumat();
    ajastin->start(timeOutAika);
}

void PaaIkkuna::on_pushButtonKirjauduUlos_clicked()
{
    ajastin->stop();
    olioDLLKortinLuku->rajapintafunktioDLLKortinLuku();
}
