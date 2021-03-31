#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QApplication>

//#include "C:\Users\keijo\Desktop\Projekti2\BankSimulPaaIkkuna\Kate.dll"

static bool createConnection()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("");
    db.setDatabaseName("");
    db.setUserName("");
    db.setPassword("");
    if (!db.open())
    {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
        qApp->tr("Unable to establish a database connection.\n"),
        QMessageBox::Cancel);
        return false;
    }

    return true;
}

#endif // CONNECTION_H
