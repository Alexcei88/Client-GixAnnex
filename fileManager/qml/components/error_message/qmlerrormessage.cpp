#include "qmlerrormessage.h"
#include <iostream>

//----------------------------------------------------------------------------------------/
QMLErrorMessage::QMLErrorMessage(QWidget *parent)
{
    box = new QMessageBox(parent);
}
//----------------------------------------------------------------------------------------/
QMLErrorMessage::~QMLErrorMessage()
{
    delete box;
    box = 0;
}
//----------------------------------------------------------------------------------------/
void QMLErrorMessage::showErrorMessage(QVariant title, QVariant text) const
{
    QMessageBox::critical(box, title.toString(), text.toString());
}
//----------------------------------------------------------------------------------------/

