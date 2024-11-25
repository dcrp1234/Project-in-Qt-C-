#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QTime t = QTime::currentTime();
    close = new QPushButton("Close");
    close->setStyleSheet("background-color: lightblue;");
    close->setFixedSize(100, 50);
    container = new QWidget();
    vlayout = new QVBoxLayout();
    hlayout1 = new QHBoxLayout();
    hlayout2 = new QHBoxLayout();
    hlayout3 = new QHBoxLayout();
    hlayout4 = new QHBoxLayout();
    hlayout5 = new QHBoxLayout();
    hlayout6 = new QHBoxLayout();
    hlayout7 = new QHBoxLayout();
    l1 = new QLabel("HOURS: BLUE PROGRESS BAR FOR PM AND YELLOW PROGRESS BAR FOR AM");
    l2 = new QLabel("MINUTES:");
    l3 = new QLabel("SECONDS:");
    rw = new RulerWidget(this, 60);
    rwm = new RulerWidget(this, 60);
    rwh =  new RulerWidget(this, 12);

    //setting the height of the scales
    rw->setMaximumHeight(height());
    rwm->setMaximumHeight(height());
    rwh->setMaximumHeight(height());

    //for second time
    clock1 = new Clock(this, "#a6c7e0", "#408ac2", "#336387");
    clock1->setValue(t.second());
    clock1->setMaximum(59);
    QTimer *timer = new QTimer(clock1);
    connect(timer, SIGNAL(timeout()), clock1, SLOT(timeo()));
    timer->start(1000);

    //for minute time
    clock2 = new Clock(this, "#a6c7e0", "#145e96", "#336387");
    clock2->setValue(t.minute());
    clock2->setMaximum(60);
    QTimer *timerm = new QTimer(clock2);
    connect(timerm, SIGNAL(timeout()), clock2, SLOT(timeo()));
    timerm->start(60000);

    //for hours
    int f = t.hour() /12;
    if( f == 0){
        clock3 = new Clock(this, "#9e98ab", "#fab505", "#665220", 2);
    }
    else {
        clock3 = new Clock(this, "#7d7391", "#372066", "#336387", 3);
    }
    clock3->setValue((t.hour() %12));
    clock3->setMaximum(12);
    QTimer *timerh = new QTimer(clock3);
    connect(timerh, SIGNAL(timeout()), clock3, SLOT(timeo()));
    timerh->start(3600000);

    connect(close, SIGNAL(clicked()), this, SLOT(close()));
    hlayout1->addWidget(rwh);
    hlayout2->addWidget(clock3);
    hlayout3->addWidget(rwm);
    hlayout4->addWidget(clock2);
    hlayout5->addWidget(rw);
    hlayout6->addWidget(clock1);
    hlayout7->addWidget(close);

    vlayout->addWidget(l1);
    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout2);
    vlayout->addWidget(l2);
    vlayout->addLayout(hlayout3);
    vlayout->addLayout(hlayout4);
    vlayout->addWidget(l3);
    vlayout->addLayout(hlayout5);
    vlayout->addLayout(hlayout6);
    vlayout->addSpacerItem(new QSpacerItem(40, 40, QSizePolicy::Expanding, QSizePolicy::Fixed));
    vlayout->addLayout(hlayout7);

    container->setLayout(vlayout);
    this->setCentralWidget(container);

}






