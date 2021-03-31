#ifndef MAKSALASKUMOOTTORI_H
#define MAKSALASKUMOOTTORI_H

#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QApplication>
#include <QMessageBox>
#include <QPushButton>
#include <QTableView>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlQuery>
#include <QLineEdit>
#include <QComboBox>
#include <QDialog>
#include <QString>
#include <QDebug>
#include <QDebug>
#include <QLabel>

namespace Ui {
class MaksaLaskuMOOTTORI;
}

class MaksaLaskuMOOTTORI : public QDialog
{
    Q_OBJECT

public:
    explicit MaksaLaskuMOOTTORI(QWidget *parent = nullptr);
    ~MaksaLaskuMOOTTORI();

    void uusiKateDB();
    void comboPaivitys(int uusiMaara);

private slots:
    void on_pushButtonPOISTU_clicked();

    void on_pushButtonMAKSALASKU_clicked();

    void on_comboBoxMISTAMAKSETAAN_currentIndexChanged(const QString &arg1);


private:
    Ui::MaksaLaskuMOOTTORI *ui;

    int laskujenMaara;

    short tiliID;

    short laskuID;

    QString tilinKate;

    QString laskuttajaUlos;

    QString Kayttotili = "FI1234567891234567";

    QString Saastotili = "FI9988776655443322";

    double summa_lasku;

    double jaljelleJaavaKate;
};

#endif // MAKSALASKUMOOTTORI_H
