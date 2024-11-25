#ifndef SECONDWINDOW_H
#define SECONDWINDOW_H

#include <QDialog>
#include <QtSql>
#include <QFile>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QTextStream>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtWidgets/QApplication>
#include <QScrollArea>
#include <QLineEdit>
#include <QPushButton>
#include <QValueAxis>
#include <QDesktopServices>
#include <QUrl>
#include <QMessageBox>

#include "data.h"

class SecondWindow : public QDialog
{
    Q_OBJECT
public:
    SecondWindow(QWidget* parent=0);
    void initalise(QSqlDatabase d, int i, Data *data);
    void extractData();
    void showGraph();
    void createForm();
    void mortgage();

private slots:
    void storeFormData();

private:
    QSqlDatabase db, t;
    int idd;
    QLabel *l1, *l2, *l3, *l4, *imgLabel, *description;
    QLabel *form;
    QLineEdit *name, *email, *phone, *note;
    QVBoxLayout *v, *fv;
    QScrollArea *scrollArea;
    QPushButton *b;
    Data *data;
    QWidget* formW;
    QWidget *scrollWidget;
};

#endif // SECONDWINDOW_H
