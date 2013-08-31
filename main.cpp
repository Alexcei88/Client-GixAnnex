#include "mainWidget.h"
#include <QApplication>
#include "tshell.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    TShell shell;
    w.show();

    return a.exec();
}
