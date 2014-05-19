#include "systemtray.h"
#include <QQuickItem>
#include <QList>
#include <iostream>
#include <assert.h>

//----------------------------------------------------------------------------------------/
SystemTray::SystemTray():
    mainView(nullptr)
  , addRepoView(nullptr)
  , preferencesAppRepoView(nullptr)
{
    //=================================================================================== /
    addRepoAction = new QAction(tr("&Add Repository"), this);
    connect(addRepoAction, SIGNAL(triggered()), this, SLOT(ShowAddRepository()));

    preferencesAction = new QAction(tr("&Preferences"), this);
    connect(preferencesAction, SIGNAL(triggered()), this, SLOT(PreferencesApplication()));

    quitAction      = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(QuitProgramm()));

    //=================================================================================== /
    trayIconMenu    = new QMenu(this);
    trayIconMenu->addAction(addRepoAction);
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
void SystemTray::ShowAddRepository()
{
    if(addRepoView)
    {
        addRepoView->show();
    }
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
    addRepoView = nullptr;
    mainView = nullptr;
    preferencesAppRepoView = nullptr;
    qApp->quit();
}
//----------------------------------------------------------------------------------------/
void SystemTray::ShowMessageNotification(  const QString& title
                                         , const QString& message
                                         , QSystemTrayIcon::MessageIcon icon
                                         , int millisecondsTimeoutHint) const
{
    Q_UNUSED(millisecondsTimeoutHint)
    trayIcon->showMessage(title, message);
}
//----------------------------------------------------------------------------------------/
void SystemTray::CloseAddRepository() const
{
    if(addRepoView)
        addRepoView->hide();
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
bool SystemTray::ResultAddRepository(const QString& text) const
{
    if(addRepoView && addRepoView->isVisible())
    {
        QObjectList parent = addRepoView->rootObject()->findChildren<QObject*>("StackView");
        return QMetaObject::invokeMethod(parent[0], "resultClone", Q_ARG(QVariant, text));
    }
}
//----------------------------------------------------------------------------------------/
bool SystemTray::HideWindowWaitCommand() const
{
    if(mainView)
    {
        QObjectList parent = mainView->rootObject()->children();
        QList<QObject*> object = parent[1]->findChildren<QObject*>(QString("directoryView"));
        assert(object.size() > 0);
        return QMetaObject::invokeMethod(object[0], "hideWaitCommandFinish", Qt::BlockingQueuedConnection);
    }
    return false;
}
//----------------------------------------------------------------------------------------/
bool SystemTray::SendErrorToView(const QString& description, const QString& nameRepository) const
{
    if(mainView)
    {
        QObjectList parent = mainView->rootObject()->children();
        QList<QObject*> object = parent[1]->findChildren<QObject*>(QString("contentItemView"));
        assert(object.size() > 0);
        return QMetaObject::invokeMethod(object[0], "appendError", Qt::BlockingQueuedConnection, Q_ARG(QVariant, description),
                                                                                                 Q_ARG(QVariant, nameRepository));
    }
    return false;
}
//----------------------------------------------------------------------------------------/
