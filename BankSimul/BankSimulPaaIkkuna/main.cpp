#include "paaikkuna.h"
#include <QApplication>
#include <QWidget>
#include <QtWidgets>
#include <QtSql>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include "connection.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PaaIkkuna w;
    if (!createConnection()) // suljetaan sovellus jos yhteys tietokantaan ei onnistu
        return 1;

/* Testi, että yhdistäminen onnistuu ja tauluista saadaan tietoa ulos

    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("Asiakas");
    model->select();

    for (int i = 0; i < model->rowCount(); ++i)
    {
        QSqlRecord record = model->record(i);
        //int id = record.value("id_henkilo").toInt();
        //QString etu = record.value("firstname").toString();
        //QString suku = record.value("lastname").toString();
        qDebug() << model->record(i);
        qDebug() << model->rowCount();
    }

 Testin loppu */

    w.show(); //avataan pääikkuna
    w.runDLLKortinLuku();   //avataan kirjautumisikkuna

    return a.exec();
}
