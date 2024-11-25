#ifndef CLOCK_H
#define CLOCK_H

#include <QProgressBar>
#include <QColor>
#include <QLinearGradient>

class Clock : public QProgressBar
{
    Q_OBJECT

public:
   Clock(QWidget *parent = nullptr, QString a="#ffffff", QString b= "#ffffff", QString c="#ffffff", int d= 1);
    ~Clock();

public slots:
    void timeo();

protected:
   void paintEvent(QPaintEvent *);



private:
   void draw(QPainter *painter, QRect rect, int w);
   void drawEllipticalRectangle(QPainter *painter, QRect rect, int w);
   QString bgc;
   QString pbc;
   QString ec;
   QLinearGradient g1, g2;
   int hgt;

};
#endif // CLOCK_H
