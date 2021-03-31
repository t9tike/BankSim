#ifndef KORTINLUKUMOOTTORIDIALOG_H
#define KORTINLUKUMOOTTORIDIALOG_H

#include <QDialog>

namespace Ui {
class KortinLukuMoottoriDialog;
}

class KortinLukuMoottoriDialog : public QDialog
{
    Q_OBJECT

public:
    explicit KortinLukuMoottoriDialog(QWidget *parent = nullptr);
    ~KortinLukuMoottoriDialog();

private:
    Ui::KortinLukuMoottoriDialog *ui;
};

#endif // KORTINLUKUMOOTTORIDIALOG_H
