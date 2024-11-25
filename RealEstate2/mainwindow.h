#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QBoxLayout>
#include <QWidget>
#include <QApplication>
#include <QLabel>
#include <QDebug>
#include <QString>
#include <QScrollBar>
#include <QGridLayout>
#include <QScrollArea>
#include <vector>
#include <QLineEdit>

#include "data.h"
#include "neighbourlist.h"
#include "cardwidget.h"
#include "secondwindow.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void createGrid();
    void createCard();
    void setUpScrollBar();
    void buttonStyle(QPushButton *p);
    void setWidgetHeight(QWidget* q, int h);

private slots:
    void showDialog();
    void displayN(QString);
    void getID(int);
    void searchDatabase();

private:
    QPushButton *close, *neighbour, *recentlySold, *searchButton;
    QWidget *container;
    QVBoxLayout *vlayout, *nlayout;
    QHBoxLayout *hlayout1, *hlayout2, *hlayout3, *hlayout4, *hlayout5, *hlayout6, *hlayout7, *hlayout0;
    QScrollBar* sb;
    QLabel *head, *headsub, *nhead, *nheadsub, *imgLabel;
    NeighbourList* nl;
    Data d;
    std::vector <CardWidget*> c1;
    QGridLayout *gridLayout, *soldLayout;
    QScrollArea *scrollArea;
    QLineEdit *search;
    SecondWindow *display;

};
#endif // MAINWINDOW_H
