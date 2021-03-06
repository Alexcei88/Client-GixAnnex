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

// функция, выполняющаяся по завершению работы программы
void Exit()
{
    FacadeApplication::RemoveInstance();
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    if(!QSystemTrayIcon::isSystemTrayAvailable()) {
        printf("System Tray Icon not avaible!!! Programma will close!");
        flush(std::cout);
        return 1;
    }

    if(!QSystemTrayIcon::supportsMessages()) {
        printf("Message not supports!!! Programma will close!");
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
    cloneRepoViewer.setMainQmlFile(QStringLiteral("qml/fileManager/repository/CloneRepositoryWizard.qml"));
    cloneRepoViewer.setMinimumHeight(500);
    cloneRepoViewer.setMinimumWidth(640);
    cloneRepoViewer.setMaximumHeight(cloneRepoViewer.minimumHeight());
    cloneRepoViewer.setMaximumWidth(cloneRepoViewer.minimumWidth());
    cloneRepoViewer.setX(300);
    cloneRepoViewer.setY(300);
    cloneRepoViewer.setTitle("Git-Annex Add Repository");
//    cloneRepoViewer.show();

    // свойства приложения
    QtQuick2ApplicationViewer preferencesAppViewer;
    preferencesAppViewer.setMainQmlFile(QStringLiteral("qml/fileManager/PreferencesApplication.qml"));
    preferencesAppViewer.setMinimumHeight(400);
    preferencesAppViewer.setMinimumWidth(500);
    preferencesAppViewer.setMaximumHeight(preferencesAppViewer.minimumHeight());
    preferencesAppViewer.setMaximumWidth(preferencesAppViewer.minimumWidth());
    preferencesAppViewer.setX(400);
    preferencesAppViewer.setY(300);
    preferencesAppViewer.setModality(Qt::ApplicationModal);
//    preferencesAppViewer.setModality(Qt::WindowModality);
    preferencesAppViewer.setTitle("Preferences Git-Annex");
    //preferencesAppViewer.show();
    //=========================================================================== /

    // создаем классы трея и передаем нужные для управления viewer-ы
    SystemTray windowTray;
    windowTray.SetMainView(&mainViewer);
    windowTray.SetAddRepoView(&cloneRepoViewer);
    windowTray.SetPreferencesApplicationView(&preferencesAppViewer);
    facadeApp->SetSystemTray(&windowTray);


    windowTray.ShowMessageNotification("Test", "ffffffvv");
    windowTray.ShowMessageNotification("Test", "ffffffvv");
    windowTray.ShowMessageNotification("Test", "ffffffvv");
    windowTray.ShowMessageNotification("Test", "ffffffvv");

    atexit(Exit);
    return app.exec();
}
