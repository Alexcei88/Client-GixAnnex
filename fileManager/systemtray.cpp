#include "systemtray.h"
#include <QQuickItem>
#include <QList>
#include <iostream>

//----------------------------------------------------------------------------------------/
SystemTray::SystemTray():
    mainView(nullptr)
  , cloneRepoView(nullptr)
  , preferencesAppRepoView(nullptr)
{
    //=================================================================================== /
    addRepoAction   = new QAction(tr("&New repository"), this);

    cloneRepoAction = new QAction(tr("&Clone Repository"), this);
    connect(cloneRepoAction, SIGNAL(triggered()), this, SLOT(CloneRepository()));

    cloneRepoAction = new QAction(tr("&Clone Repository"), this);
    connect(cloneRepoAction, SIGNAL(triggered()), this, SLOT(CloneRepository()));

    preferencesAction = new QAction(tr("&Preferences"), this);
    connect(preferencesAction, SIGNAL(triggered()), this, SLOT(PreferencesApplication()));

    quitAction      = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(QuitProgramm()));

    //=================================================================================== /
    trayIconMenu    = new QMenu(this);
    trayIconMenu->addAction(addRepoAction);
    trayIconMenu->addAction(cloneRepoAction);
    trayIconMenu->addAction(preferencesAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon        = new QSystemTrayIcon(QIcon(":/heart.ico"), this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->show();

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(ActivateTray(QSystemTrayIcon::ActivationReason)));
}
//----------------------------------------------------------------------------------------/
void SystemTray::ActivateTray(QSystemTrayIcon::ActivationReason reason)
{
//    std::cout<<"Reason = "<<reason<<std::endl;
    switch(reason)
    {
        case QSystemTrayIcon::Context:
            trayIcon->contextMenu()->show();
            break;

        case QSystemTrayIcon::Trigger:
            if(mainView)
            {
                mainView->show();
            }
            break;
        default: break;
    }
}
//----------------------------------------------------------------------------------------/
void SystemTray::CloneRepository()
{
    if(cloneRepoView)
        cloneRepoView->show();
}
//----------------------------------------------------------------------------------------/
void SystemTray::PreferencesApplication()
{
    if(preferencesAppRepoView)
        preferencesAppRepoView->show();
}
//----------------------------------------------------------------------------------------/
void SystemTray::QuitProgramm()
{
    cloneRepoView = nullptr;
    mainView = nullptr;
    preferencesAppRepoView = nullptr;
    qApp->quit();
}
//----------------------------------------------------------------------------------------/
void SystemTray::CancelCloneRepository() const
{
    if(cloneRepoView)
        cloneRepoView->hide();
}
//----------------------------------------------------------------------------------------/
void SystemTray::ClosePreferencesApplication() const
{
    if(preferencesAppRepoView)
        preferencesAppRepoView->hide();
}
//----------------------------------------------------------------------------------------/
bool SystemTray::ReLoadListRepository() const
{
    if(mainView)
    {
        QObjectList parent = mainView->rootObject()->children();
        QList<QObject*> object = parent[1]->findChildren<QObject*>(QString("listRepository"));
        return QMetaObject::invokeMethod(object[0], "reloadModel");
    }
    return false;
}
//----------------------------------------------------------------------------------------/
bool SystemTray::OnUpdateIconsSyncronization() const
{
    if(mainView && mainView->isVisible())
    {
        QObjectList parent = mainView->rootObject()->children();
        QList<QObject*> object = parent[1]->findChildren<QObject*>(QString("directoryView"));
        return QMetaObject::invokeMethod(object[0], "updateIconsStateFileSync", Qt::BlockingQueuedConnection);
    }
    return false;
}
//----------------------------------------------------------------------------------------/
