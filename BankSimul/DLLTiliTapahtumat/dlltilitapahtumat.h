#ifndef DLLTILITAPAHTUMAT_H
#define DLLTILITAPAHTUMAT_H

#include "dlltilitapahtumat_global.h"
#include "tilitapahtumatmoottoridialog.h"

#include <QtSql>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QObject>

class DLLTILITAPAHTUMATSHARED_EXPORT DLLTiliTapahtumat
{

public:
    DLLTiliTapahtumat();
    ~DLLTiliTapahtumat();
    void DLLTILITAPAHTUMATSHARED_EXPORT rajapintafunktioDLLTiliTapahtumat(); //rajapintafunktio, jota kutsutaan pääikkunassa

private:
    TiliTapahtumatMoottoriDialog * olioTiliTapahtumatMoottoriDialog;

};

#endif // DLLTILITAPAHTUMAT_H
