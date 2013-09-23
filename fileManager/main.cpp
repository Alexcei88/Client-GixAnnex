#include <QtGui/QGuiApplication>
#include <QGuiApplication>
#include "qtquick2applicationviewer.h"
#include <QSystemTrayIcon>
#include <QApplication>

// системное меню
#include <systemtray.h>

// ради теста
#include "repository/trepository.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // создаем нам нужные вьюверы
    QtQuick2ApplicationViewer viewer;
    viewer.setMainQmlFile(QStringLiteral("qml/fileManager/main.qml"));
    viewer.setMinimumHeight(500);
    viewer.setMinimumWidth(400);
    viewer.setTitle("Git-Annex Client");
    viewer.show();

    if(!QSystemTrayIcon::isSystemTrayAvailable()) {
        printf("System Tray Icon not avaible!!! Programma will close!");
        flush(std::cout);
        return 1;
    }
    // при закрытии последнего окна приложение работу не завершает, она будет висеть в трее
    QApplication::setQuitOnLastWindowClosed(false);

    SystemTray windowTray;

    TRepository rep;
//    rep.CloneRepository("MyRepo", "https://github.com/Alexcei88/Employer.git", "/home/alexcei/Copy/");
//    flush(std::cout);
    return app.exec();
}
