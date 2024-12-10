#ifndef NEIGHBOURLIST_H
#define NEIGHBOURLIST_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QDebug>


class NeighbourList : public QDialog
{
    Q_OBJECT
public:
    NeighbourList(QWidget* parent = 0);

signals:
    void sendNeighbour(QString s);

private slots:
    void addButtonClicked(QString s);

private:
    QVBoxLayout *v;
    QPushButton* Downtown;
    QPushButton* Riverside;
    QPushButton* Cooperwood;
    QPushButton* Lakeview;
    QString s;
};

#endif // NEIGHBOURLIST_H
