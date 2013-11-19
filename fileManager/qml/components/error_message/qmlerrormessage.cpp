#include "qmlerrormessage.h"
#include <iostream>

QMLErrorMessage::QMLErrorMessage(QWidget *parent)
{
    box = new QMessageBox(parent);
}

QMLErrorMessage::~QMLErrorMessage()
{
    delete box;
    box = 0;
}

void QMLErrorMessage::ShowErrorMessage() const
{
    std::cout<<"ShowErrorMessage"<<std::endl;
    box->show();
}
