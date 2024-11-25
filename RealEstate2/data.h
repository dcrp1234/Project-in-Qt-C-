#ifndef DATA_H
#define DATA_H

#include <QtSql>
#include <QFile>
#include <QSqlQuery>
#include <QSqlDatabase>

class Data
{

public:
    Data();
    ~Data(){}
    void createDatabase();
    void createTuples(QSqlQuery query, QString);
    QSqlDatabase  getDatabase();
    void createTable(QString n, QString e, int p, QString no);

private:
    QSqlDatabase db;
};

#endif // DATA_H
