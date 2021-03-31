#include "kortinlukumoottoridialog.h"
#include "ui_kortinlukumoottoridialog.h"

KortinLukuMoottoriDialog::KortinLukuMoottoriDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KortinLukuMoottoriDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Kirjaudu Sisään");
}

KortinLukuMoottoriDialog::~KortinLukuMoottoriDialog()
{
    delete ui;
}

