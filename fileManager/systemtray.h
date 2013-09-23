#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QApplication>


class SystemTray : public QWidget
{
    Q_OBJECT

public:
    SystemTray();

public slots:
    // слот, отвечающий за обработку нажатия по иконке мышью
    void            ActivateTray(QSystemTrayIcon::ActivationReason reason);

private:

    QSystemTrayIcon* trayIcon;
    QMenu*          trayIconMenu;

    QAction*        addRepoAction;
    QAction*        cloneRepoAction;
    QAction*        quitAction;
};

#endif // SYSTEMTRAY_H
