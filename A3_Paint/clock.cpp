#include "clock.h"
#include <QPainter>
#include <QPainterPath>
#include <QGradient>

Clock::Clock(QWidget *parent, QString a, QString b, QString c, int d)
    : QProgressBar(parent)
{
    bgc = a;
    pbc = b;
    ec = c;
    hgt= d;
}

Clock::~Clock()
{
}

void Clock::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int borde = height()/20;

    draw(&painter,
         QRect(borde+4, borde, (width())-2*borde -8, height()-2*borde),
         2*borde);
}

void Clock::draw(QPainter *painter, QRect rect, int w)
{
    //draws the three parts of the progress bar
    int w_percentage = 2*w + value()*(rect.width()-2*w)/maximum();
    //int k= 1;
        QLinearGradient gradient1(rect.topLeft(), rect.bottomRight());
        gradient1.setColorAt(0, "#f6d365");
        gradient1.setColorAt(1, "#fda085");

        QLinearGradient gradient2(rect.topLeft(), rect.bottomRight());
        gradient2.setColorAt(1, "#330867");
        gradient2.setColorAt(0, "#30cfd0");

       if(hgt==2){
           //clock is an hour clock then set gradient
           painter->setBrush(gradient1);
           //k=2;
       }
       else if(hgt==3){
           painter->setBrush(gradient2);
         //  k=2;
       }
       else {
           //for minute and second progress bar
           painter->setBrush(QBrush(QColor(pbc)));
       }


    //the progress bar
    drawEllipticalRectangle(painter,
                            QRect(rect.topLeft(), QSize(w_percentage, rect.height()) ),
                            w);

    //the background
    painter->setBrush(QBrush(QColor(bgc)));
    drawEllipticalRectangle(painter,
                            QRect(QPoint(rect.topLeft() + QPoint(w_percentage-4*w, 0)),
                                  QSize(rect.width()-w_percentage+4*w, rect.height()) ),
                            w);

    //small ellipse
    painter->setBrush(QBrush(QColor(ec)));
    painter->drawEllipse(QRect( rect.topLeft() + QPoint(rect.width()-3*w, 0) , QSize(2*w, rect.height())));

}


void Clock::drawEllipticalRectangle(QPainter *painter, QRect rect, int w)
{//draws the elliptical rectangles
    painter->translate(rect.topLeft());

    QPainterPath path;

    path.moveTo(w, 0);
    path.arcTo(QRectF(0, 0, 2*w, rect.height()), 90, 180);
    path.lineTo(rect.width()-w, rect.height());

    path.arcTo(QRectF(rect.width()-2*w, 0, 2*w, rect.height()), 270, -180);
    path.lineTo(w, 0);
    painter->drawPath(path);

    painter->translate(-rect.topLeft());
}

void Clock::timeo(){
    setValue((value()+1)%(1 + maximum()));
}
