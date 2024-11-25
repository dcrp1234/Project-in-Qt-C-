#include <QMainWindow>
#include "cardwidget.h"

CardWidget::CardWidget(QWidget* parent, int i, QString p, QString be, QString ba, QString a, QString r, QString m)
{
    price=p; bed =be; bath = ba; addr = a; realtor=r; MLS=m; id=i;
    vlayout= new QVBoxLayout(this);
    l1= new QLabel(this);
    l2= new QLabel(this);
    l3= new QLabel(this);
    l4= new QLabel(this);
    imgLabel = new QLabel(this);
    setFixedSize(parent->width(), parent->height());//sets size of image
    c= new QWidget(this);
    c->setLayout(vlayout);
    c->setMaximumHeight(parent->height());
    c->setMaximumWidth(parent->width());
    qDebug() << parent->width() <<parent->height();
    qDebug()<< width()/2<<height()/2;
    qDebug() << width() <<height();

   // connect(parent, SIGNAL(resized()), this , SLOT(cardResize()));

    c->setStyleSheet("QWidget{ background-color: blue;}");
    address = new QPushButton(addr);
    address->setStyleSheet("border: none;");
    connect(address, SIGNAL(clicked()), this, SLOT(addButtonClicked()));

}
void CardWidget::cardResize(){
    setFixedSize(width()/2, height()/2);
    c->setMaximumSize(width()/2, height()/2);
}
void CardWidget::addDescription(){
    l1->setText("$" + price);
    l2->setText(bed + "bed" + bath + "bath");
    l4->setText(MLS + " " + realtor);
    address->setCursor(Qt::PointingHandCursor);
    vlayout->addWidget(l1);
    vlayout->addWidget(l2);
    vlayout->addWidget(address);
    vlayout->addWidget(l4);
}
void CardWidget::addImage(QString img){
    // Load and display image
    QPixmap image(img);
    if (!image.isNull()) {
        imgLabel->setPixmap(image.scaled(width(), width(), Qt::KeepAspectRatio)); // Set image size as required
    } else {
        qDebug() << "Failed to load image from path:" << img;
    }
    vlayout->addWidget(imgLabel);
}

void CardWidget::addButtonClicked(){
    emit sendID(id);
}
