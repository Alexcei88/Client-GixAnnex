#include "systemtray.h"
#include <QQuickItem>
#include <QList>
#include <iostream>

//----------------------------------------------------------------------------------------/
SystemTray::SystemTray():
    mainView(0l)
  , cloneRepoView(0l)
{
    //=================================================================================== /
    addRepoAction   = new QAction(tr("&New repository"), this);

    cloneRepoAction = new QAction(tr("&Clone Repository"), this);
    connect(cloneRepoAction, SIGNAL(triggered()), this, SLOT(CloneRepository()));

    quitAction      = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    //=================================================================================== /

    trayIconMenu    = new QMenu(this);
    trayIconMenu->addAction(addRepoAction);
    trayIconMenu->addAction(cloneRepoAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon    = new QSystemTrayIcon(QIcon(":/heart.ico"), this);
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
void SystemTray::CancelCloneRepository() const
{
    if(cloneRepoView)
        cloneRepoView->hide();
}
//----------------------------------------------------------------------------------------/
bool SystemTray::ReLoadListRepository() const
{
    if(mainView)
    {
        QObjectList parent = mainView->rootObject()->children();
        QObjectList parentItem = parent[0]->children();
        QObjectList itemChildren = parentItem[2]->children();
        return QMetaObject::invokeMethod(itemChildren[0], "reloadModel");
    }
    return false;
}
//----------------------------------------------------------------------------------------/
bool SystemTray::ReLoadDirectoryView() const
{
    if(mainView)
    {
        QObjectList parent = mainView->rootObject()->children();
        QList<QObject*> object = parent[1]->findChildren<QObject*>(QString("directoryView"));
        return QMetaObject::invokeMethod(object[0], "updateIconsStateFileSync");
    }
    return false;
}
//----------------------------------------------------------------------------------------/
