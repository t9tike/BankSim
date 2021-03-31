#ifndef DIALOGUI_H
#define DIALOGUI_H

#include <QSqlTableModel>
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
#include <QLabel>


namespace Ui {
class DialogUI;
}

class DialogUI : public QDialog
{
    Q_OBJECT

public:
    explicit DialogUI(QWidget *parent = nullptr);
    ~DialogUI();
    void tiliNumero1();
    void tiliNumero2();
    void naytaKateT1();
    void naytaKateT2();
    void uusiKate();
    void tulostaUusiKate();

private slots:

    void on_NAPPIJOU_clicked();

    void on_pushButtonPOISTU_clicked();

    void on_comboBoxTilinValinta_currentIndexChanged(const QString &arg1);

private:
    Ui::DialogUI *ui;
    short   kytkin =1;

    double  nostettavaSumma =0;

    double  tilinKate =0;

    double  tulevaKate =0;

    QString uusikate;

    int     ID_Nosto =0;

    short   tiliID =6;
};

#endif // DIALOGUI_H
