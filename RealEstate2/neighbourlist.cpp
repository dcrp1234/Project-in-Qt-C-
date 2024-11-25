#include "neighbourlist.h"

NeighbourList::NeighbourList(QWidget* parent): QDialog(parent)
{
    v = new QVBoxLayout();
    Cooperwood = new QPushButton("Cooperwood");
    Riverside= new QPushButton("Riverside");
    Lakeview= new QPushButton("Lakeview");
    Downtown= new QPushButton("Downtown");

    v->addWidget(Cooperwood);
    v->addWidget(Riverside);
    v->addWidget(Lakeview);
    v->addWidget(Downtown);

    this->setLayout(v);


     connect(Downtown, &QPushButton::clicked, [=]() {addButtonClicked("Downtown");});
     connect(Cooperwood, &QPushButton::clicked, [=]() {addButtonClicked("Cooperwood");});
     connect(Lakeview, &QPushButton::clicked, [=]() {addButtonClicked("Lakeview");});
     connect(Riverside, &QPushButton::clicked, [=]() {addButtonClicked("Riverside");});

}


void NeighbourList::addButtonClicked(QString s){
    emit sendN(s);
}
