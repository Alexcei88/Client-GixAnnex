#include <QtGui/QGuiApplication>
#include <QGuiApplication>
#include "qtquick2applicationviewer.h"
#include <QSystemTrayIcon>
#include <QApplication>

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
    // создаем нам нужные вьюверы
    // главный viewer
    QtQuick2ApplicationViewer mainViewer;
    mainViewer.setMainQmlFile(QStringLiteral("qml/fileManager/main.qml"));
    mainViewer.setMinimumHeight(500);
    mainViewer.setMinimumWidth(400);
    mainViewer.setTitle("Git-Annex Client");

    // viewer копирования репозитория
    QtQuick2ApplicationViewer cloneRepoViewer;
    cloneRepoViewer.setMainQmlFile(QStringLiteral("qml/fileManager/repository/clone.qml"));
    cloneRepoViewer.setMinimumHeight(60);
    cloneRepoViewer.setMinimumWidth(300);
    cloneRepoViewer.setX(600);
    cloneRepoViewer.setY(300);

    cloneRepoViewer.setTitle("Git-Annex Clone Repository");

    //=========================================================================== /

    // создаем классы трея и передаем нужные для управления viewer-ы
    SystemTray windowTray;
    windowTray.SetMainView(&mainViewer);
    windowTray.SetCloneRepoView(&cloneRepoViewer);

    //=========================================================================== /
    // Фасад приложения
    FacadeApplication* facadeApp = FacadeApplication::getInstance();
    facadeApp->SaveRepository(QString("Vacz"), QString("OTpEty"), QString("Friend"));


    TRepository rep;
//    rep.CloneRepository("MyRepo", "https://github.com/Alexcei88/Employer.git", "/home/alexcei/Copy/");
//    flush(std::cout);
    return app.exec();
}
