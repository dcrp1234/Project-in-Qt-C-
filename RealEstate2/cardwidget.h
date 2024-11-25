#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QPixmap>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QString>
#include <QVBoxLayout>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QPushButton>

class CardWidget : public QWidget
{
    Q_OBJECT
public:
    CardWidget(QWidget* parent= nullptr,int id=0, QString price= "", QString bed= "", QString bath= "", QString addr= "", QString realtor= "", QString MLS= "");
    ~CardWidget(){}
    void addDescription();
    void addImage(QString);

signals:
    void sendID(int);

private slots:
    void addButtonClicked();
    void cardResize();

private:
    QVBoxLayout *vlayout;
    QLabel *l1, *l2, *l3, *l4, *imgLabel;
    QPushButton* address;
    QString price, bed, bath, addr, realtor, MLS;
    int id;
    QWidget *c;
};

#endif // CARDWIDGET_H
