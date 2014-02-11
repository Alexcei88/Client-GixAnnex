#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QQuickView>


class SystemTray : public QWidget
{
    Q_OBJECT

public:
    SystemTray();

    inline void         SetMainView(QQuickView* view) { this->mainView = view; }
    inline void         SetCloneRepoView(QQuickView* view) { this->cloneRepoView = view; }
    inline void         SetPreferencesApplicationView(QQuickView* view) { this->preferencesAppRepoView = view; }

    void                CancelCloneRepository() const;
    void                ClosePreferencesApplication() const;

    /** @brief Перезагрузить модель со списком репозиториев */
    bool                ReLoadListRepository() const;

    /** @brief Обновить состояние иконок синхронизации */
    bool                OnUpdateIconsSyncronization() const;

public slots:
    /** @brief Нажатия по иконке мышью */
    void                ActivateTray(QSystemTrayIcon::ActivationReason reason);
    /** @brief Запуск окна клонирования репозитория */
    void                CloneRepository();
    /** @brief Запуск окна свойств репозитория */
    void                PreferencesApplication();

    /** @brief Закрытие программы */
    void                QuitProgramm();

private:

    QSystemTrayIcon*    trayIcon;
    QMenu*              trayIconMenu;

    QAction*            addRepoAction;
    QAction*            cloneRepoAction;
    QAction*            preferencesAction;
    QAction*            quitAction;

    // viewer-ы
    /** @brief главный вид */
    QQuickView*         mainView;
    /** @brief вид окна клонирования репозитория */
    QQuickView*         cloneRepoView;
    /** @brief вид окна свойств репозитория */
    QQuickView*         preferencesAppRepoView;

};

#endif // SYSTEMTRAY_H
