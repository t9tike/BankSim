#ifndef PINKOODIDIALOG_H
#define PINKOODIDIALOG_H

#include <QMessageBox>
#include <QDialog>
#include <QtSql>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>

namespace Ui {
class PinKoodiDialog;
}

class PinKoodiDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PinKoodiDialog(QWidget *parent = nullptr);
    ~PinKoodiDialog();
    void cardSerialNumberTallennus(QString lahetettySerial); //tallenetaan dllkortinluvun lähettämä kortin numero

signals:
    void signaaliPinKoodiOikein(); //lähetetään signaali dllkortinluvulle, kun pin-koodi on syötetty oikein

private slots:
    void on_pushButtonOk_clicked();

    void on_pushButtonKeskeyta_clicked();

private:
    Ui::PinKoodiDialog *ui;
    QString cardSerialNumber;
};

#endif // PINKOODIDIALOG_H
