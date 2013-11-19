#include <QtGui/QGuiApplication>
#include <QGuiApplication>
#include "qtquick2applicationviewer.h"
#include <QSystemTrayIcon>
#include <QApplication>
#include <QObject>
#include <QMetaObject>

// системное меню
#include "systemtray.h"

// фасад приложения
#include "facadeapplication.h"

// ради теста
#include "repository/trepository.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if(!QSystemTrayIcon::isSystemTrayAvailable()) {
        printf("System Tray Icon not avaible!!! Programma will close!");
        flush(std::cout);
        return 1;
    }
    // при закрытии последнего окна приложение работу не завершает, оно будет висеть в трее
    QApplication::setQuitOnLastWindowClosed(false);

    //=========================================================================== /
    // Фасад приложения
    FacadeApplication* facadeApp = FacadeApplication::getInstance();

    //=========================================================================== /

    //=========================================================================== /
    // создаем нам нужные вьюверы
    // главный viewer
    QtQuick2ApplicationViewer mainViewer;
    mainViewer.setMainQmlFile(QStringLiteral("qml/fileManager/main.qml"));
    mainViewer.setMinimumHeight(500);
    mainViewer.setMinimumWidth(400);
    mainViewer.setTitle("Git-Annex Client");
    mainViewer.show();

    // viewer копирования репозитория
    QtQuick2ApplicationViewer cloneRepoViewer;
    cloneRepoViewer.setMainQmlFile(QStringLiteral("qml/fileManager/repository/Clone.qml"));
    cloneRepoViewer.setMinimumHeight(170);
    cloneRepoViewer.setMinimumWidth(540);
    cloneRepoViewer.setMaximumHeight(cloneRepoViewer.minimumHeight());
    cloneRepoViewer.setMaximumWidth(cloneRepoViewer.minimumWidth());
    cloneRepoViewer.setX(600);
    cloneRepoViewer.setY(300);    
    cloneRepoViewer.setTitle("Git-Annex Clone Repository");

    //=========================================================================== /

    // создаем классы трея и передаем нужные для управления viewer-ы
    SystemTray windowTray;
    windowTray.SetMainView(&mainViewer);
    windowTray.SetCloneRepoView(&cloneRepoViewer);
    facadeApp->SetSystemTray(&windowTray);

    //TRepository rep;
//    rep.CloneRepository("/home/alexcei/Copy/copyproject", "MyRepo", "/home/alexcei/Copy/project");
//    rep.GetContentFile(".");
    flush(std::cout);
    return app.exec();
}
