#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QHBoxLayout>
#include <QWidget>
#include <QApplication>
#include <QProgressBar>
#include <QLabel>
#include <QTimer>
#include <QTime>
#include <QString>
#include <QRect>

#include "clock.h"
#include "ruler.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    QPushButton *close;
    QWidget *container;
    QVBoxLayout *vlayout;
    QHBoxLayout *hlayout1, *hlayout2, *hlayout3, *hlayout4, *hlayout5, *hlayout6, *hlayout7;
    Clock *clock1;
    Clock *clock2;
    Clock *clock3;
    RulerWidget *rw;
    RulerWidget *rwm;
    RulerWidget *rwh;
    QLabel *l1, *l2, *l3;

};

#endif // MAINWINDOW_H
