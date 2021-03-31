#include "tilitapahtumatmoottoridialog.h"
#include "ui_tilitapahtumatmoottoridialog.h"

TiliTapahtumatMoottoriDialog::TiliTapahtumatMoottoriDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TiliTapahtumatMoottoriDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Tilitapahtumat");
    nostojenKirjaaminen();  //haetaan nostojen tiedot tietokannasta ja kirjataan ne
    laskujenKirjaaminen();  //haetaan laskujen tiedot tietokannasta ja kirjataan ne
    siirtojenKirjaaminen(); //haetaan siirtojen tiedot tietokannasta ja kirjataan ne
}

TiliTapahtumatMoottoriDialog::~TiliTapahtumatMoottoriDialog()
{
    delete ui;
}

void TiliTapahtumatMoottoriDialog::on_pushButton_clicked()
{
    this->close();  //sulkee komponentin ja palataan pääikkunanäkymään
}

void TiliTapahtumatMoottoriDialog::nostojenKirjaaminen() //funktio hakee nostojen tiedot tietokannasta
{
    int nostoIndex = 0;     //kasvava muuttuja, joka kertoo taulukkojen indexin
    double nostoSummat[4];  //taulukko nostosummien tallentamiseen
    int id_tilit[4];        //taulukko tilinumerojen tallentamiseen

    QSqlTableModel model;
    model.setTable("Nosto");    //valitaan tietokannasta nosto-taulu
    model.select();
    int viimeinenRivi = model.rowCount() - 1;   //asetetaan muuttuja viimeiselle riville, jotta saadaan viimeisimmät nostot kaivettua tietokannasta

    for (int i = viimeinenRivi; i > viimeinenRivi - 4; --i) //for-loop tallentaa neljän viimeisimmän noston tiedot edellä määritellyihin taulukoihin.
    {
        QSqlRecord record = model.record(i);
        //int id_nosto = record.value("id_nosto").toInt();
        //qDebug() << "id_nosto:" << id_nosto;
        id_tilit[nostoIndex] = record.value("id_tili").toInt();
        //qDebug() << "id_tili:" << id_tilit[nostoIndex];
        nostoSummat[nostoIndex] = record.value("summa_nosto").toDouble();
        //qDebug() << "summa_nosto:" << nostoSummat[nostoIndex];
        nostoIndex++;
    }

    nostoSummienKirjoittaminenUI(nostoSummat, 4); //funktio kirjoittaa nostosummat näytölle

    model.setTable("Tili"); //valitaan tietokannasta Tili-taulu
    model.select();
    QString tiliNumerot[4]; //luodaan taulukko, johon tilinumerot tallennetaan QString-muodossa

    for (int i = 0; i<4; i++)  //for loopissa tallenetaan Tili-taulusta tilinumerot Nosto-taulusta haettujen tili-id:den avulla
    {
        QSqlRecord record = model.record(id_tilit[i] -1);
        tiliNumerot[i] = record.value("tilinumero_asiakas").toString();
        //qDebug() << "tilin id on:" << id_tilit[i] << "ja tämän tilin tilinumero on:" << tiliNumerot[i];
    }

    nostoTilienKirjoittaminenUI(tiliNumerot); //funktio kirjoittaa nostojen tilinumerot näytölle

}

void TiliTapahtumatMoottoriDialog::nostoSummienKirjoittaminenUI(double *array, int arraySize) //funktio kirjoittaa nostosummat näytölle
{
    QString summaString[arraySize];
    for (int i = 0; i <= arraySize; i++) // for-loop muuntaa summat doublesta Qstringiksi
    {
        summaString[i] = QString::number(array[i]);
    }

    ui->labelHaettuNostoSumma1->setText(summaString[0]); //kirjoitetaan summat labeleihin
    ui->labelHaettuNostoSumma2->setText(summaString[1]);
    ui->labelHaettuNostoSumma3->setText(summaString[2]);
    ui->labelHaettuNostoSumma4->setText(summaString[3]);
}

void TiliTapahtumatMoottoriDialog::nostoTilienKirjoittaminenUI(QString *array) //funktio kirjoittaa nostojen tilit näytölle
{
    ui->labelHaettuNostoTili1->setText(array[0]); //kirjoitetaan tilit labeleihin
    ui->labelHaettuNostoTili2->setText(array[1]);
    ui->labelHaettuNostoTili3->setText(array[2]);
    ui->labelHaettuNostoTili4->setText(array[3]);
}

void TiliTapahtumatMoottoriDialog::laskujenKirjaaminen() //funktio hakee laskujen tiedot tietokannasta
{
    QString laskuttaja[2];  //luodaan taulukot kuten edellä nosto-tapauksessa
    QString tilinumero_laskuttaja[2];
    double summa_lasku[2];

    QSqlTableModel model;
    model.setTable("Lasku");
    model.setFilter("maksun_tila = 0"); //valitaan Lasku-taulusta vain maksetut laskut, eli joissa maksun_tila == 0
    model.select();

    for (int i = 0; i < 2; ++i) //for-loop tallentaa Laskujen tiedot taulukoihin
    {
        QSqlRecord record = model.record(i);
        //int id_lasku = record.value("id_lasku").toInt();
        //qDebug() << "id_lasku:" << id_lasku;
        //int id_asiakkaanTili = record.value("id_tili").toInt();
        //qDebug() << "id_asiakkaantili:" << id_asiakkaanTili;
        laskuttaja[i] = record.value("laskuttaja").toString();
        //qDebug() << "laskuttaja:" << laskuttaja[i];
        tilinumero_laskuttaja[i] = record.value("tilinumero_laskuttaja").toString();
        //qDebug() << "tilinumero_laskuttaja:" << tilinumero_laskuttaja[i];
        summa_lasku[i] = record.value("summa_lasku").toDouble();
        //qDebug() << "summa_lasku:" << summa_lasku[i];
    }

    laskujenKirjoittaminenUI(laskuttaja, tilinumero_laskuttaja, summa_lasku); //funktio kirjoittaa laskujen tiedot näytölle
}

void TiliTapahtumatMoottoriDialog::laskujenKirjoittaminenUI(QString *laskuttaja, QString *tilinumero_laskuttaja, double *summa_lasku) //funktio kirjoittaa laskujen tiedot näytölle
{
    ui->labelHaettuLaskuLaskuttaja1->setText(laskuttaja[0]);
    ui->labelHaettuLaskuLaskuttaja2->setText(laskuttaja[1]);
    ui->labelHaettuLaskuTili1->setText(tilinumero_laskuttaja[0]);
    ui->labelHaettuLaskuTili2->setText(tilinumero_laskuttaja[1]);

    QString summa_LaskuString[2];
    for (int i = 0; i < 2; ++i) //for-loop muuntaa laskusummat doublesta QStringiksi kahden desimaalin tarkkuuteen
    {
        summa_LaskuString[i] = QString::number(summa_lasku[i], 'f', 2);
    }

    ui->labelHaettuLaskuSumma1->setText(summa_LaskuString[0]);
    ui->labelHaettuLaskuSumma2->setText(summa_LaskuString[1]);

}

void TiliTapahtumatMoottoriDialog::siirtojenKirjaaminen() //funktio hakee siirtojen tiedot tietokannasta
{
    int siirtoIndex = 0; //index samoin kuin nostossa
    double siirtoSummat[4]; //taulukot samoin kuin nostossa
    int id_tilit[4];
    QString tilinumerotVastaanottaja[4];
    QString viesti[4];

    QSqlTableModel model;
    model.setTable("Tilisiirto");
    model.select();
    int viimeinenRivi = model.rowCount() - 1; //viimeisen rivin valinta samoin kuin nostossa

    for (int i = viimeinenRivi; i > viimeinenRivi - 4; --i) //for-loop hakee tietokannasta siirtojen tiedot ja tallentaa ne taulukoihin
    {
        QSqlRecord record = model.record(i);
        //int id_siirto = record.value("id_siirto").toInt();
        //qDebug() << "id_siirto:" << id_siirto;
        id_tilit[siirtoIndex] = record.value("id_tili").toInt();
        //qDebug() << "id_tili:" << id_tilit[siirtoIndex];
        siirtoSummat[siirtoIndex] = record.value("summa_siirto").toDouble();
        //qDebug() << "summa_siirto:" << siirtoSummat[siirtoIndex];
        tilinumerotVastaanottaja[siirtoIndex] = record.value("tilinumero_vastaanottaja").toString();
        viesti[siirtoIndex] = record.value("viesti").toString();
        siirtoIndex++;
    }

    model.setTable("Tili");
    model.select();
    QString tiliNumerotLahettaja[4];

    for (int i = 0; i<4; i++) //for-loop hakee Tili-taulusta tilinumerot Siirto-taulusta haettujen tili-id:den avulla
    {
        QSqlRecord record = model.record(id_tilit[i] -1);
        tiliNumerotLahettaja[i] = record.value("tilinumero_asiakas").toString();
        //qDebug() << "tilin id on:" << id_tilit[i] << "ja tämän tilin tilinumero on:" << tiliNumerotLahettaja[i];
    }

    siirtoSummanKirjoittaminenUI(siirtoSummat); // nämä neljä funktiota kirjoittavat siirtojen tiedot näytölle
    siirtoLahettajanTilinKirjoittaminenUI(tiliNumerotLahettaja);
    siirtoVastaanottajanTilinKirjoittaminenUI(tilinumerotVastaanottaja);
    siirtoViestinKirjoittaminenUI(viesti);

}

void TiliTapahtumatMoottoriDialog::siirtoSummanKirjoittaminenUI(double *summa_siirto) //kirjoittaa siirtosummat näytölle
{
    QString summa_siirtoString[4];
    for (int i = 0; i < 4; ++i) //for-loop muuntaa summan doublesta QStringiksi kahden desimaalin tarkkuuteen
    {
        summa_siirtoString[i] = QString::number(summa_siirto[i], 'f', 2);
    }

    ui->labelHaettuSiirtoSumma1->setText(summa_siirtoString[0]);
    ui->labelHaettuSiirtoSumma2->setText(summa_siirtoString[1]);
    ui->labelHaettuSiirtoSumma3->setText(summa_siirtoString[2]);
    ui->labelHaettuSiirtoSumma4->setText(summa_siirtoString[3]);
}

void TiliTapahtumatMoottoriDialog::siirtoLahettajanTilinKirjoittaminenUI(QString *tilinumeroLahettaja) //kirjoittaa siirtojen lähettäjien tilit näytölle
{
    ui->labelHaettuSiirtoTili1->setText(tilinumeroLahettaja[0]);
    ui->labelHaettuSiirtoTili2->setText(tilinumeroLahettaja[1]);
    ui->labelHaettuSiirtoTili3->setText(tilinumeroLahettaja[2]);
    ui->labelHaettuSiirtoTili4->setText(tilinumeroLahettaja[3]);
}

void TiliTapahtumatMoottoriDialog::siirtoVastaanottajanTilinKirjoittaminenUI(QString *tilinumeroVastaanottaja) //kirjoittaa siirtojen vastaanottajien tilit näytölle
{
    ui->labelHaettuSiirtoVastaanottajanTili1->setText(tilinumeroVastaanottaja[0]);
    ui->labelHaettuSiirtoVastaanottajanTili2->setText(tilinumeroVastaanottaja[1]);
    ui->labelHaettuSiirtoVastaanottajanTili3->setText(tilinumeroVastaanottaja[2]);
    ui->labelHaettuSiirtoVastaanottajanTili4->setText(tilinumeroVastaanottaja[3]);
}

void TiliTapahtumatMoottoriDialog::siirtoViestinKirjoittaminenUI(QString *viesti) //kirjoittaa siirtojen viestit näytölle
{
    ui->labelHaettuSiirtoViesti1->setText(viesti[0]);
    ui->labelHaettuSiirtoViesti2->setText(viesti[1]);
    ui->labelHaettuSiirtoViesti3->setText(viesti[2]);
    ui->labelHaettuSiirtoViesti4->setText(viesti[3]);
}

