#include "systemtray.h"
#include <iostream>

//----------------------------------------------------------------------------------------/
SystemTray::SystemTray():
    mainView(0l)
   ,cloneRepoView(0l)
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

    trayIcon    = new QSystemTrayIcon(QIcon("qrc:/heart.ico"), this);
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
    {
        cloneRepoView->show();
    }
}
//----------------------------------------------------------------------------------------/

