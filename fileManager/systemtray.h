#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QQuickView>

/*
 * КЛАСС, УПРАВЛЯЮЩИЙ ОКНАМИ ПРИЛОЖЕНИЯ:
 * ПОКАЗ, СКРЫТИЕ ФОРМ

*/

class SystemTray : public QWidget
{
    Q_OBJECT

public:
    SystemTray();

    inline void         SetMainView(QQuickView* view) { this->mainView = view; };
    inline void         SetCloneRepoView(QQuickView* view) { this->cloneRepoView = view; };
    void                CancelCloneRepository() const;

    /** @brief перезагрузить модель со списком репозиториев */
    bool                ReLoadListRepository() const;

public slots:
    /** @brief слот, отвечающий за обработку нажатия по иконке мышью */
    void                ActivateTray(QSystemTrayIcon::ActivationReason reason);

    void                CloneRepository();
    /** @brief обновить состояние иконок синхронизации */
    bool                OnUpdateIconsSyncronization() const;

signals:
    bool                updateIconsSyncronization() const;

private:

    QSystemTrayIcon*    trayIcon;
    QMenu*              trayIconMenu;

    QAction*            addRepoAction;
    QAction*            cloneRepoAction;
    QAction*            quitAction;

    // viewer-ы
    /**
    @brief viewRepo - главный вид
    */
    QQuickView*         mainView;
    /**
    @brief cloneRepo - вид окна клонирования репозитория
    */
    QQuickView*         cloneRepoView;
};

#endif // SYSTEMTRAY_H
