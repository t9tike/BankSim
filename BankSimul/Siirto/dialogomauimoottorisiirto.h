#ifndef DIALOGOMAUIMOOTTORISIIRTO_H
#define DIALOGOMAUIMOOTTORISIIRTO_H

#include <QDialog>

namespace Ui {
class Dialogomauimoottorisiirto;
}

class Dialogomauimoottorisiirto : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogomauimoottorisiirto(QWidget *parent = nullptr);
    ~Dialogomauimoottorisiirto();
    void ekaTilinKate();
    void tokaTilinKate();
    void kolmannenTilinKate();
    void neljannenTilinKate();
    void vahennusLasku();
    void yhteenLasku();
    void tulostaUusiKate();

private slots:
    void on_pushButtonSuljeSiirto_clicked();
    void on_pushButtonPaivita_clicked();
    void on_comboBoxMista_currentIndexChanged(const QString &arg1);
    void on_comboBoxMihin_currentIndexChanged(const QString &arg1);

private:
    Ui::Dialogomauimoottorisiirto *ui;
    double  nostettavaSumma = 0;
    double tilinKate = 0;
    double tulevaKate = 0;
    short tiliID = 6;
    short tiliID2 = 6;

    int ID_Nosto = 0;
    QString uusikate2 = "0";
    QString tilinumero;
    double siirrettavaSumma;

    QString haeKate;
    double kate;

    QString uusikate3 = "0";
    QString viesti;

    short kytkin1 = 3;
    short kytkin2 = 0;
};

#endif // DIALOGOMAUIMOOTTORISIIRTO_H
