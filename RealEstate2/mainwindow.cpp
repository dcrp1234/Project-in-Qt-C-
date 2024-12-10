#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    d.createDatabase();
    QString heading= "Lethbridge Real Estate";
    QString hsub = "Refine your Lethbridge real estate search by price, bedroom.";
    container = new QWidget();
    sb = new QScrollBar(Qt::Vertical);
    scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true); // Ensures that the contents can resize

    vlayout = new QVBoxLayout();
    nlayout = new QVBoxLayout();
    hlayout0 = new QHBoxLayout();
    hlayout1 = new QHBoxLayout();
    hlayout2 = new QHBoxLayout();
    hlayout3 = new QHBoxLayout();
    hlayout4 = new QHBoxLayout();
    hlayout5 = new QHBoxLayout();
    hlayout6 = new QHBoxLayout();
    hlayout7 = new QHBoxLayout();
    gridLayout = new QGridLayout();
    soldLayout = new QGridLayout();
    imgLabel = new QLabel();
    search = new QLineEdit();
    search->setPlaceholderText("Search Neighbourhood");

    QPixmap image(":/Hi/files/logo.png");
    if (!image.isNull()) {
        imgLabel->setPixmap(image.scaled(50, 50, Qt::KeepAspectRatio)); // Set image size as required
    } else {
        qDebug() << "Failed to load image from path:" << image;
    }
    head= new QLabel(this);
    headsub = new QLabel(this);
    head->setText(heading);
    head->setStyleSheet("QLabel { font-size: 30px; }");
    headsub->setText(hsub);
    setWidgetHeight(head, 40);
    setWidgetHeight(headsub, 20);

    close = new QPushButton("Close");
    neighbour = new QPushButton("Neighbour");
    recentlySold = new QPushButton("Sold");
    searchButton = new QPushButton("Q");

    buttonStyle(neighbour);
    buttonStyle(recentlySold);

    connect(close, SIGNAL(clicked()), this, SLOT(close()));
    connect(neighbour, SIGNAL(clicked()), this, SLOT(showDialog()));
    connect(searchButton, SIGNAL(clicked()), this, SLOT(searchDatabase()));

    createGrid();
    createCard();

    hlayout0->addWidget(imgLabel);
    hlayout0->addWidget(search);
    hlayout0->addWidget(searchButton);
    hlayout1->addWidget(head);
    hlayout2->addWidget(headsub);
    hlayout3->addWidget(neighbour);
    hlayout3->addWidget(recentlySold);
    hlayout3->setAlignment(Qt::AlignLeft); // Align the layout to the left
    setUpScrollBar();

    vlayout->addLayout(hlayout0);
    vlayout->addLayout(hlayout1);
    vlayout->addLayout(hlayout2);
    vlayout->addLayout(hlayout3);
    vlayout->addLayout(hlayout4);

    container->setLayout(vlayout);
    this->setCentralWidget(container);
}

void MainWindow::showDialog(){
    // if(!nl) {
    nl = new NeighbourList(this);
    connect(nl, SIGNAL(sendNeighbour(QString)), this, SLOT(getNeighbour(QString)));
    // }
    nl->show();
    nl->activateWindow();
}

void MainWindow::getNeighbour(QString s){
    if(s!=""){
        //search and display the new house list in the main window by deleting current widgets and adding new widgets
        QSqlDatabase db = d.getDatabase();
        if (!db.open()) {
            qDebug() << "Error: Failed to open database";
        }
        else{
            qDebug() <<"Database opened, searching for neighbourhood "<< s;
            QSqlQuery query("SELECT * FROM Home", db); // Replace with your table name
            int i=0;
            int p=0, q=0;//for fixing the coordinates for the two grid layouts
            while (query.next()) {
                //qDebug() << "Running through all queries";
                if (query.value("neighbour").toString() == s ){
                    int id= query.value("id").toInt();
                    int status= query.value("status").toInt();
                    QString price = query.value("price").toString();
                    QString address = query.value("address").toString();
                    QString bed = query.value("bed").toString();
                    QString bath = query.value("bath").toString();
                    QString realtor = query.value("realtor").toString();
                    QString mls = query.value("mls").toString();
                    QString img = query.value("img").toString();

                    // Do something with the extracted data, such as printing it
                    qDebug() << "Title:" << mls << "Neighbourt:" << query.value("neighbour").toString();
                    if(search->text()==mls || search->text().contains(address, Qt::CaseInsensitive )){
                        CardWidget *cw = new CardWidget(this, id, price, bed, bath, address, realtor, mls);
                        c1.push_back(cw);
                        if(status==1){//on sale
                            gridLayout->addWidget(c1[i], p / 2, p % 2); // Add to grid layout
                            p++;
                        }
                        else{
                            soldLayout->addWidget(c1[i], q / 2, q % 2); // Add to sold layout
                            q++;
                        }
                        c1[i]->addImage(img);
                        c1[i]->addDescription();
                        connect(c1[i], SIGNAL(sendID(int)), this, SLOT(getID(int)));
                        i++;
                        qDebug()<<"Search found";
                    }
                }
            }
            gridLayout->update();
            //inspectGridLayout(gridLayout);
            setUpScrollBar();
            db.close();
        }
    }
    else{
        qDebug()<<"Null search";
    }

}
void MainWindow::createCard(){
    QSqlDatabase db = d.getDatabase();
    if (!db.open()) {
        qDebug() << "Error: Failed to open database";
    }
    else{
        qDebug() <<"Database opened";
        QSqlQuery query("SELECT * FROM Home", db); // Replace with your table name
        int i=0;
        int p=0, q=0;//for fixing the coordinates for the two grid layouts
        while (query.next()) {
            int id= query.value("id").toInt();
            int status= query.value("status").toInt();
            QString price = query.value("price").toString();
            QString address = query.value("address").toString();
            QString bed = query.value("bed").toString();
            QString bath = query.value("bath").toString();
            QString realtor = query.value("realtor").toString();
            QString mls = query.value("mls").toString();
            QString img = query.value("img").toString();

            // Do something with the extracted data, such as printing it
            qDebug() << "Title:" << mls << "Content:" << price;
            CardWidget *cw = new CardWidget(this, id, price, bed, bath, address, realtor, mls);
            c1.push_back(cw);
            if(status==1){//on sale
                gridLayout->addWidget(c1[i], p / 2, p % 2); // Add to grid layout
                p++;
            }
            else{
                soldLayout->addWidget(c1[i], q / 2, q % 2); // Add to sold layout
                q++;
            }
            c1[i]->addImage(img);
            c1[i]->addDescription();
            connect(c1[i], SIGNAL(sendID(int)), this, SLOT(getID(int)));
            i++;
        }
        db.close();
    }
}

void MainWindow::createGrid(){

}

void MainWindow::buttonStyle(QPushButton *p){
    // Set fixed height and width
    p->setFixedSize(200, 40);

    // Apply stylesheet for round edges and custom background color
    p->setStyleSheet("QPushButton {"
                     "border-radius: 20px;" // Half of the height to make it round
                     "background-color: #C0C0C0;" // Example color, you can change this
                     "}"
                     "QPushButton:hover {"
                     "background-color: #A0A0A0;" // Example color on hover, you can change this
                     "}");

}

void MainWindow::setWidgetHeight(QWidget *q, int h){
    q->setMinimumHeight(h);
    q->setMaximumHeight(h);
}

void MainWindow::setUpScrollBar(){
    qDebug() << "inside setUpScrollBar";
    QWidget *scrollWidget;
    if (!scrollArea->widget()) {
        // Create the scroll widget if it hasn't been created yet
        scrollWidget = new QWidget;
        scrollWidget->setLayout(gridLayout);  // Set the grid layout here
        scrollArea->setWidget(scrollWidget);  // Assign the widget to the scroll area
    } else {
        // If the widget already exists, just update the layout inside it
        scrollWidget = scrollArea->widget();
        scrollWidget->setLayout(gridLayout);  // Update the layout to gridLayout
    }

    // Connect scrollbar to scroll area
    QObject::connect(sb, &QScrollBar::valueChanged, scrollArea->verticalScrollBar(), &QScrollBar::setValue);

    // Set scrollbar range and page step
    sb->setRange(0, scrollWidget->height() - scrollArea->viewport()->height());
    sb->setPageStep(scrollArea->viewport()->height());

    hlayout4->addWidget(sb);
    hlayout4->addWidget(scrollArea);
}

void MainWindow::getID(int id){
    // qDebug() << "Printing in mainWindow getID function,  address buttion clciked with id" << id;
    //if(!display){
    display = new SecondWindow(this);
    display->initalise(d.getDatabase(), id, &d);
    //}
    display->show();
    display->activateWindow();
}

void MainWindow::searchDatabase(){

}

MainWindow::~MainWindow()
{

}
void inspectGridLayout(QGridLayout *gridLayout) {
    int rowCount = gridLayout->rowCount();
    int colCount = gridLayout->columnCount();

    qDebug() << "Grid Layout Contents:";
    for (int row = 0; row < rowCount; ++row) {
        for (int col = 0; col < colCount; ++col) {
            QLayoutItem *item = gridLayout->itemAtPosition(row, col);
            if (item) {
                QWidget *widget = item->widget();
                if (widget) {
                    // Here you can check the widget or print some information about it
                    qDebug() << "Widget at position (" << row << "," << col << "):"
                             << widget->objectName();  // Print widget name or any other info
                } else {
                    qDebug() << "No widget at position (" << row << "," << col << ")";
                }
            }
        }
    }
}


