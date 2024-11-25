#include "ruler.h"
#include <QPainter>

RulerWidget::~RulerWidget(){}

void RulerWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    endX=width();
    //updateEndX();

    double tickSpacing = (endX-11)/(parts); // Adjust the spacing between ticks, need endX -8 to leave 4 units before and after the scale
    int tickLength = 10;   // Adjust the length of ticks

    painter.setPen(Qt::black);
    painter.drawLine(startX+2, height(), endX-11 , height()); // Draw baseline

    for (int i = 0; i <= parts; i++) {
        a = startX+2+ i*tickSpacing+1.5;
        if(i%(parts/12)==0){
            painter.drawLine(a, height(), a, height()-5 - tickLength); // Draw longer tick
            if (i == parts){
                painter.drawText(a-10, height()-10 -tickLength, QString::number(i)); // Draw label
            }
            else
             painter.drawText(a-5, height()-10 -tickLength, QString::number(i)); // Draw label for the last one

        }
        else {
            painter.drawLine(a, height(), a, height() - tickLength); // Draw small tick

        }
    }
}
