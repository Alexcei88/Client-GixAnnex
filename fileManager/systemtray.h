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
    inline void         SetAddRepoView(QQuickView* view) { this->addRepoView = view; }
    inline void         SetPreferencesApplicationView(QQuickView* view) { this->preferencesAppRepoView = view; }

    /** @brief Показать системное уведомление */
    void                ShowMessageNotification(  const QString& title
                                                , const QString& message
                                                , QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::Information
                                                , int millisecondsTimeoutHint = 10000) const;

    /** @brief Закрыть окно добавления репозитория */
    void                CloseAddRepository() const;

    /** @brief Закрыть окно со свойствами приложения */   
    void                CancelCloneRepository() const;
    void                ClosePreferencesApplication() const;

    /** @brief Перезагрузить модель со списком репозиториев */
    bool                ReLoadListRepository() const;

    /** @brief Обновить состояние иконок синхронизации */
    bool                OnUpdateIconsSyncronization() const;

    /** @brief Сообщаем, что клонирование завершилось */
    bool                ResultAddRepository(const QString& text) const;
    /** @brief Скрыть окно завершения окончания команды */
    bool                HideWindowWaitCommand() const;

public slots:
    /** @brief Нажатия по иконке мышью */
    void                ActivateTray(QSystemTrayIcon::ActivationReason reason);
    /** @brief Запуск окна добавления репозитория */
    void                ShowAddRepository();
    /** @brief Запуск окна свойств репозитория */
    void                PreferencesApplication();

    /** @brief Закрытие программы */
    void                QuitProgramm();

private:

    QSystemTrayIcon*    trayIcon;
    QMenu*              trayIconMenu;

    QAction*            addRepoAction;
    QAction*            preferencesAction;
    QAction*            quitAction;

    // viewer-ы
    /** @brief главный вид */
    QQuickView*         mainView;
    /** @brief вид окна добавления репозитория */
    QQuickView*         addRepoView;

    /** @brief вид окна свойств репозитория */
    QQuickView*         preferencesAppRepoView;

};

#endif // SYSTEMTRAY_H
