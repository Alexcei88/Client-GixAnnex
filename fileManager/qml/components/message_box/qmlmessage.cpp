#include "qmlmessage.h"
#include <iostream>

//----------------------------------------------------------------------------------------/
QMLMessage::QMLMessage(QWidget *parent)
{
    box = new QMessageBox(parent);
}
//----------------------------------------------------------------------------------------/
QMLMessage::~QMLMessage()
{
    delete box;
    box = 0;
}
//----------------------------------------------------------------------------------------/
void QMLMessage::showErrorMessage(QVariant title, QVariant text) const
{
    QMessageBox::critical(box, title.toString(), text.toString());
}
//----------------------------------------------------------------------------------------/

