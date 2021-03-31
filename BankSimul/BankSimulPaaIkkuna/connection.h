#ifndef CONNECTION_H
#define CONNECTION_H

#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QApplication>


static bool createConnection()  // Luodaan yhteys tietokantaan
{
    QSqlDatabase db = QSqlDatabase::addDatabase("*sql*");  //määritellään, minkälaista tietokantaa käytetään
    db.setHostName("**");        //täytetään kirjautumistiedot
    db.setDatabaseName("**");
    db.setUserName("**");
    db.setPassword("*");
    if (!db.open()) //jos yhteyttä ei saada muodostettua, ilmoitetaan siitä
    {
        QMessageBox::critical(0, qApp->tr("Cannot open database"),
        qApp->tr("Unable to establish a database connection.\n"),
        QMessageBox::Cancel);
        return false;
    }

    return true;
}

#endif // CONNECTION_H
