#include "data.h"

Data::Data()
{
}

void Data::createDatabase(){
    qDebug() << "Available database drivers:" << QSqlDatabase::drivers();     // Print available database drivers

    // Create a connection to the SQLite database
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("House_Database.db"); // Set the database name

    //deletes existing database
    QFile file("House_Database.db");
    if (file.exists()) {
        if (!file.remove()) {
            qDebug() << "Error: Failed to delete existing database file";
        } else {
            qDebug() << "Existing database file deleted successfully";
        }
    }

    // Open the database
    if (!db.open()) {
        qDebug() << "Failed to open database:";
        qDebug() << db.lastError().text();
    }
    else{
        // Database opened successfully
        qDebug() << "Database opened successfully.";

        // Create a table
        QSqlQuery query, query2;
        if (!query.exec("CREATE TABLE IF NOT EXISTS Home (id INTEGER PRIMARY KEY,status INTEGER, price INTEGER, bed INTEGER, bath INTEGER, address TEXT, neighbour TEXT, realtor TEXT, mls TEXT, des TEXT, img TEXT)")) {
            qDebug() << "Failed to create table:";
            qDebug() << query.lastError().text();
        }
        else{
            //qDebug() << "Table created successfully.";

            // Insert some data
            createTuples(query, "INSERT INTO Home (status, price, bed, bath, address, neighbour, realtor, mls, des, img) VALUES (1, 400000, 4, 3, 'XXX Columbia Blvd West', 'Cooperwood', 'Sutton', 'A200000', ':/Des/files/descriptions/1.txt', ':/Hi/files/front/1.jpg' )");
            createTuples(query, "INSERT INTO Home (status, price, bed, bath, address, neighbour, realtor, mls, des, img) VALUES (2, 590000, 3, 3, 'XXX Acquatania Blvd West', 'Lakeview', 'ReMax', 'A200290', ':/Des/files/descriptions/2.txt', ':/Hi/files/front/2.jpg' )");
            createTuples(query, "INSERT INTO Home (status, price, bed, bath, address, neighbour, realtor, mls, des, img) VALUES (1, 350000, 3, 2, '123 Main Street', 'Downtown', 'Century21', 'A123456', ':/Des/files/descriptions/3.txt', ':/Hi/files/front/3.jpg' )");
            createTuples(query, "INSERT INTO Home (status, price, bed, bath, address, neighbour, realtor, mls, des, img) VALUES (2, 450000, 4, 3, '456 Elm Street', 'Downtown', 'Coldwell Banker', 'B789012', ':/Des/files/descriptions/4.txt', ':/Hi/files/front/4.jpg' )");
            createTuples(query, "INSERT INTO Home (status, price, bed, bath, address, neighbour, realtor, mls, des, img) VALUES (2, 550000, 5, 4, '789 Oak Street', 'Riverside', 'Keller Williams', 'C345678' , ':/Des/files/descriptions/5.txt', ':/Hi/files/front/5.jpg')");
            createTuples(query, "INSERT INTO Home (status, price, bed, bath, address, neighbour, realtor, mls, des, img) VALUES (1, 650000, 2, 2, '101 Pine Street', 'Cooperwood', 'RE/MAX', 'D901234' , ':/Des/files/descriptions/6.txt', ':/Hi/files/front/6.jpg')");
            createTuples(query, "INSERT INTO Home (status, price, bed, bath, address, neighbour, realtor, mls, des, img) VALUES (1, 750000, 5, 4, '202 Maple Street', 'Lakeview', 'Royal LePage', 'E567890', ':/Des/files/descriptions/7.txt', ':/Hi/files/front/7.jpg' )");
            createTuples(query, "INSERT INTO Home (status, price, bed, bath, address, neighbour, realtor, mls, des, img) VALUES (2, 600000, 4, 3, '300 Cedar Street', 'Riverside', 'Century21', 'F123450', ':/Des/files/descriptions/8.txt', ':/Hi/files/front/8.jpeg' )");
            createTuples(query, "INSERT INTO Home (status, price, bed, bath, address, neighbour, realtor, mls, des, img) VALUES (1, 700000, 5, 4, '404 Pine Avenue', 'Downtown', 'Coldwell Banker', 'G234567', ':/Des/files/descriptions/9.txt', ':/Hi/files/front/9.jpeg' )");
            createTuples(query, "INSERT INTO Home (status, price, bed, bath, address, neighbour, realtor, mls, des, img) VALUES (2, 800000, 4, 3, '505 Maple Court', 'Cooperwood', 'RE/MAX', 'H345678', ':/Des/files/descriptions/10.txt', ':/Hi/files/front/10.jpg')");
            createTuples(query, "INSERT INTO Home (status, price, bed, bath, address, neighbour, realtor, mls, des, img) VALUES (1, 900000, 5, 4, '606 Elm Way', 'Lakeview', 'Royal LePage', 'I456789', ':/Des/files/descriptions/11.txt', ':/Hi/files/front/11.jpg')");
            createTuples(query, "INSERT INTO Home (status, price, bed, bath, address, neighbour, realtor, mls, des, img) VALUES (1, 1000000, 6, 3, '707 Oak Lane', 'Riverside', 'Century21', 'J567890', ':/Des/files/descriptions/12.txt', ':/Hi/files/front/12.jpg')");
            createTuples(query, "INSERT INTO Home (status, price, bed, bath, address, neighbour, realtor, mls, des, img) VALUES (1, 1100000, 5, 4, '808 Cedar Circle', 'Downtown', 'Coldwell Banker', 'K678901', ':/Des/files/descriptions/13.txt', ':/Hi/files/front/13.jpg')");
            createTuples(query, "INSERT INTO Home (status, price, bed, bath, address, neighbour, realtor, mls, des, img) VALUES (2, 1200000, 4, 3, '909 Pine Avenue', 'Cooperwood', 'RE/MAX', 'L789012', ':/Des/files/descriptions/14.txt', ':/Hi/files/front/14.jpg')");
            createTuples(query, "INSERT INTO Home (status, price, bed, bath, address, neighbour, realtor, mls, des, img) VALUES (1, 1300000, 5, 4, '1010 Maple Court', 'Lakeview', 'Royal LePage', 'M890123', ':/Des/files/descriptions/15.txt', ':/Hi/files/front/15.jpg')");

        }
        if(!query2.exec("CREATE TABLE IF NOT EXISTS Trend(id INTEGER PRIMARY KEY,dec INTEGER, jan INTEGER,feb INTEGER)")) {
            qDebug() << "Failed to create table:";
            qDebug() << query.lastError().text();
        }
        else {
            qDebug() << "Trend table created successfully.";
            createTuples(query, "INSERT INTO Trend (dec, jan, feb) VALUES (400000, 420000, 350000)");
            createTuples(query, "INSERT INTO Trend (dec, jan, feb) VALUES (620000, 550000, 650000)");
            createTuples(query, "INSERT INTO Trend (dec, jan, feb) VALUES (350000, 370000, 350000)");
            createTuples(query, "INSERT INTO Trend (dec, jan, feb) VALUES (620000, 550000, 650000)");
            createTuples(query, "INSERT INTO Trend (dec, jan, feb) VALUES (620000, 570000, 550000)");
            createTuples(query, "INSERT INTO Trend (dec, jan, feb) VALUES (620000, 650000, 680000)");
            createTuples(query, "INSERT INTO Trend (dec, jan, feb) VALUES (720000, 730000, 750000)");
            createTuples(query, "INSERT INTO Trend (dec, jan, feb) VALUES (450000, 480000, 500000)");
            createTuples(query, "INSERT INTO Trend (dec, jan, feb) VALUES (550000, 520000, 480000)");
            createTuples(query, "INSERT INTO Trend (dec, jan, feb) VALUES (400000, 420000, 450000)");
            createTuples(query, "INSERT INTO Trend (dec, jan, feb) VALUES (620000, 640000, 660000)");
            createTuples(query, "INSERT INTO Trend (dec, jan, feb) VALUES (610000, 590000, 580000)");
            createTuples(query, "INSERT INTO Trend (dec, jan, feb) VALUES (720000, 710000, 690000)");
            createTuples(query, "INSERT INTO Trend (dec, jan, feb) VALUES (800000, 820000, 840000)");
            createTuples(query, "INSERT INTO Trend (dec, jan, feb) VALUES (900000, 880000, 870000)");

        }
    }
}

void Data::createTuples(QSqlQuery query, QString q){
    if (!query.exec(q)) {
        qDebug() << "Failed to insert data:";
        qDebug() << query.lastError().text();
    }
    //  qDebug() << "Data inserted successfully.";
}

QSqlDatabase Data::getDatabase(){
    return db;
}

void Data::createTable(QString n, QString e, int p, QString no){
    if (!db.open()) {
        qDebug() << "Failed to open database:";
        qDebug() << db.lastError().text();
    }
    else{
        // Database opened successfully
        qDebug() << "Database opened successfully.";

        // Create a table
        QSqlQuery query;
        if (!query.exec("CREATE TABLE IF NOT EXISTS User (id INTEGER PRIMARY KEY, name TEXT, email TEXT, phone INTEGER, note TEXT)")) {
            qDebug() << "Failed to create table:";
            qDebug() << query.lastError().text();
        }
        else{
            qDebug() << "Table opened successfully.";

            // Insert data into the table
            QString insertQuery = QString("INSERT INTO User (name, email, phone, note) VALUES ('%1', '%2', %3, '%4')")
                                      .arg(n).arg(e).arg(p).arg(no);
            if (!query.exec(insertQuery)) {
                qDebug() << "Failed to insert data:";
                qDebug() << query.lastError().text();
            }
            else {
                qDebug() << "Data inserted successfully.";
            }

        }
        db.close();
    }
}
