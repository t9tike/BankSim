#ifndef DIALOGOMAUIMOOTTORIDIALOG_H
#define DIALOGOMAUIMOOTTORIDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QSqlQuery>

namespace Ui {
class DialogOmaUIMoottoriDialog;
}

class DialogOmaUIMoottoriDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DialogOmaUIMoottoriDialog(QWidget *parent = nullptr);
    ~DialogOmaUIMoottoriDialog();

private slots:
    void on_pushButtonSuljeKate_clicked();
    void on_pushButtonSiirraTekstia_clicked();

private:
    Ui::DialogOmaUIMoottoriDialog *ui;
    bool katePaivitys = 1;                      // Päivitysnapin tarkistamiseen
};

#endif // DIALOGOMAUIMOOTTORIDIALOG_H
