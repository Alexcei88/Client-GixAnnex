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
QVariant QMLMessage::showConfirmMessage(QVariant title, QVariant text) const
{
    if(QMessageBox::question(box, title.toString(), text.toString()) == QMessageBox::Yes)
        return 1;
    else
        return 0;
}
//----------------------------------------------------------------------------------------/
QVariant QMLMessage::showWarningMessage(QVariant title, QVariant text) const
{
    int result = QMessageBox::warning(box, title.toString(), text.toString(), QMessageBox::Ok, QMessageBox::Cancel);
    return result == QMessageBox::Ok;
}
//----------------------------------------------------------------------------------------/
