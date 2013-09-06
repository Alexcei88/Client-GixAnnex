#include <QtGui/QGuiApplication>
#include "qtquick2applicationviewer.h"

// ради теста
#include "repository/trepository.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/fileManager/main.qml"));
    viewer.setMinimumHeight(500);
    viewer.setMinimumWidth(400);
//    viewer.hide();
    viewer.setTitle("Git-Annex Client");
    viewer.show();

    TRepository rep;
    rep.CloneRepository("MyRepo", "https://github.com/Alexcei88/Employer.git", "/home/alexcei/Copy/");
    flush(std::cout);
    return app.exec();
}
