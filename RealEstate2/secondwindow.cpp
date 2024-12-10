#include "secondwindow.h"

//QT_CHARTS_USE_NAMESPACE
SecondWindow::SecondWindow(QWidget* parent) : QDialog(parent)
{
    setFixedSize(parent->width(), parent->height());
}

void SecondWindow::initalise(QSqlDatabase d, int i, Data *da){
    db = d;
    idd = i;
    data =da;
    // qDebug() << "inside SecondWindow" << idd;
    formW = new QWidget(this);

    l1= new QLabel(this);
    l2= new QLabel(this);
    l3= new QLabel(this);
    imgLabel= new QLabel(this);
    description = new QLabel(this);
    v = new QVBoxLayout();
    form = new QLabel(this);
    name = new QLineEdit();
    email = new QLineEdit();
    phone = new QLineEdit();
    note = new QLineEdit();
    fv = new QVBoxLayout();
    b=new QPushButton("Go Tour this House");
    b->setCursor(Qt::PointingHandCursor);
    v->setContentsMargins(10, 10, 10, 10); // Adjust the margins as needed
    v->setSpacing(15);
    scrollArea = new QScrollArea(this);
    scrollArea->setFixedSize(width(), height());
    scrollArea->setWidgetResizable(true); // Ensures that the contents can resize
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scrollWidget = new QWidget(this);
    scrollWidget->setLayout(v); // Assuming gridLayout is the layout that needs to be scrolled
    qDebug()<<width();
    if(width()>650){
        scrollWidget->setMinimumWidth(width()*0.60);
        scrollWidget->setMaximumWidth(width()*0.60);
    }
    else{
        scrollWidget->setMinimumWidth(width()*0.98);
        scrollWidget->setMaximumWidth(width()*0.98);
    }
    scrollArea->setWidget(scrollWidget);
    extractData();
    showGraph();
    createForm();
}

void SecondWindow::extractData(){
    if (!db.open()) {
        qDebug() << "Error: Failed to open database";
    }
    else{

        QString price, address, bed, bath, realtor, mls, neighbour, img, des, fileContent;

        qDebug() <<"Database opened";
        QSqlQuery query("SELECT * FROM Home", db);

        int i=0;
        while (query.next()) {
            int id= query.value("id").toInt();
            if(idd==id){
                price = query.value("price").toString();
                address = query.value("address").toString();
                bed = query.value("bed").toString();
                bath = query.value("bath").toString();
                realtor = query.value("realtor").toString();
                mls = query.value("mls").toString();
                neighbour = query.value("neighbour").toString();
                img = query.value("img").toString();
                des = query.value("des").toString();

                break;
            }
            i++;
        }

        //allocates the data to the QLabels
        l1->setText(address);
        l1->setStyleSheet("QLabel { font-size: 22px; }");

        l2->setText("Lethbridge, " + neighbour);
        l3->setText("$" +price);
        l3->setStyleSheet("QLabel { font-size: 30px; }");
        QPixmap image(img);
        if (!image.isNull()) {
            imgLabel->setPixmap(image.scaled(scrollWidget->width(), scrollWidget->width(), Qt::KeepAspectRatio)); // Set image size as required
        } else {
            qDebug() << "Failed to load image from path:" << img;
        }

        QFile file(des);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Error: Cannot open file" << des;
        }
        else{
            // Read the contents of the file
            QTextStream in(&file);
            fileContent = in.readAll();

            // Close the file
            file.close();
        }

        description->setText(fileContent);
        description->setWordWrap(true); // Enable word wrapping
        QLabel *q= new QLabel("Description");
        v->addWidget(imgLabel);
        v->addWidget(l1);
        v->addWidget(l2);
        v->addWidget(l3);
        mortgage();
        v->addWidget(q);
        q->setStyleSheet("QLabel { font-size: 20px; }");

        v->addWidget(description);

        db.close();
    }

}

void SecondWindow::showGraph(){
    QLineSeries *series = new QLineSeries();
    int i=0, id;
    double d, j, f;

    if (!db.open()) {
        qDebug() << "Error: Failed to open database";
    }
    else{
        qDebug() <<"Database opened";
        QSqlQuery query("SELECT * FROM Trend", db);

        while (query.next()) {
            id= query.value("id").toInt();
            if(idd==id){
                d= query.value("dec").toInt();
                j= query.value("jan").toInt();
                f= query.value("feb").toInt();
                d=d/100000;
                j=j/100000;
                f=f/100000;

                series->append(0, d);
                series->append(1, j);
                series->append(2, f);
                break;
            }
            i++;
        }

    }
    // Create a chart and add the line series to it
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Trend");
    //chart->createDefaultAxes();
    QValueAxis *axisX = new QValueAxis;
    QValueAxis *axisY = new QValueAxis;
    axisX->setTitleText("Months");
    axisY->setTitleText("Price in terms of 100000");
    // Assuming you have minimum and maximum values for X and Y axes
    double minXValue = 0.0; // Example minimum value for X axis
    double maxXValue = 5.0; // Example maximum value for X axis
    double minYValue = 0.0; // Example minimum value for Y axis
    double maxYValue = 10.0; // Example maximum value for Y axis

    // Set range for X axis
    axisX->setRange(minXValue, maxXValue);
    axisX->setTickCount(6);
    axisX->setLabelFormat("%.0f");
    // Set range for Y axis
    axisY->setRange(minYValue, maxYValue);

    // Add axes to the chart
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    // Associate the series with the axes
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    // Create a chart view and set the chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumHeight(400);
    chartView->setMinimumWidth(300);
    v->addWidget(chartView);
}

void SecondWindow::createForm(){
    form->setText("Ask About this Home");
    form->setStyleSheet("font-size: 22px");
    name->setPlaceholderText("Full name");
    email->setPlaceholderText("Email");
    phone->setPlaceholderText("Phone number");
    note->setPlaceholderText("Note");
    fv->setSpacing(20);
    name->setStyleSheet("border: 1px solid black;border-radius: 5px; height: 30px;");
    email->setStyleSheet("border: 1px solid black;border-radius: 5px;height: 30px;");
    phone->setStyleSheet("border: 1px solid black;border-radius: 5px;height: 30px;");
    note->setStyleSheet("border: 1px solid black;border-radius: 5px;height: 30px;");
    b->setStyleSheet("background-color: green; border-radius: 10px; height: 40px;color: white;");

    fv->addWidget(form);
    fv->addWidget(name);
    fv->addWidget(email);
    fv->addWidget(phone);
    fv->addWidget(note);
    fv->addWidget(b);
    formW->setLayout(fv);
    formW->setMaximumWidth(400);
    formW->setStyleSheet("background-color: white; border-radius: 10px;");
    v->addWidget(formW);
    connect(b, SIGNAL(clicked()), this, SLOT(storeFormData()));
}

void SecondWindow::storeFormData(){
    QString n= name->text();
    QString e= email->text();
    int p= (phone->text()).toInt();
    QString no= note->text();
    if(n!="" && p!=0 && (p/1000000000)!=0 && (e!="" && e.contains('@') && e.contains('.'))){
        data->createTable(n,e,p,no);
        // Remove all widgets from the layout
        QLayoutItem* item;
        while ((item = fv->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }

        // SecondWindow thank you message
        QLabel* thankYouLabel = new QLabel("Thank you!", this);
        thankYouLabel->setAlignment(Qt::AlignCenter);
        fv->addWidget(thankYouLabel);
        formW->setLayout(fv);
        formW->setMinimumHeight(300);
    }
    else if (p!=0 && (p/1000000000)==0){
        qDebug() <<"Empty incorrect phone number";
        QMessageBox::critical(nullptr, "Error", "Phone number not valid.",QMessageBox::Ok );
    }
    else if ( e!="" && (!e.contains('@') || !e.contains('.'))){
        qDebug() <<"Empty incorrect email";
        QMessageBox::critical(nullptr, "Error", "Email not valid.",QMessageBox::Ok );
    }
    else{
        qDebug() <<"Empty values cannot be accepted";
        QMessageBox::critical(nullptr, "Error", "Cannot submit empty form.",QMessageBox::Ok);
    }
}

void SecondWindow::mortgage() {
    QLabel *m= new QLabel();
    m->setText("With rates as low as xxx, you can spend less on your mortage with XXXMortgage.");
    m->setWordWrap(true); // Enable text wrapping
    QPushButton *pb = new QPushButton("LEARN MORE");
    pb->setStyleSheet("background-color: green; color: white;");
    pb->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    pb->setCursor(Qt::PointingHandCursor);
    QHBoxLayout *h= new QHBoxLayout();
    h->setSpacing(10); // Adjust as needed

    h->addWidget(m);
    h->addWidget(pb);
    QWidget *mort = new QWidget(this);
    mort->setMinimumHeight(46);

    mort->setLayout(h);
    mort->setStyleSheet("background-color: black; color:white; font-family: Arial; font-size: 18pt;");
    v->addWidget(mort);
    connect(pb, &QPushButton::clicked, [=]() {
        // Open the link in the default web browser
        QDesktopServices::openUrl(QUrl("https://www.truenorthmortgage.ca/rates/lethbridge"));
    });
}
