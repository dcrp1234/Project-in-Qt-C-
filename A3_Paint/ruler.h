#ifndef RULER_H
#define RULER_H

#include <QWidget>
#include <QPainter>

class RulerWidget : public QWidget {
    Q_OBJECT
public:
    RulerWidget(QWidget *parent = nullptr, int a =1): QWidget(parent) {
        updateEndX();
        parts = a;
    }
    ~RulerWidget();

protected:
    void paintEvent(QPaintEvent *);

private:
    void updateEndX() {
         if (parentWidget()) {
             endX = parentWidget()->width()-16;
             startX =4;
             a=0;
         }
     }
    int startX ;
    int endX;
    int parts;
    int a;
};

#endif // RULERWIDGET_H
