#ifndef FACADEAPPLICATION_H
#define FACADEAPPLICATION_H

/*
 * КЛАСС-СИНГЛЕТОН, УПРАВЛЯЮЩИЙ ПРИЛОЖЕНИЕМ
 * В ЕГО ОТВЕТСТВЕННОСТЬ ВХОДИТ:
 * - КОНФИГУРИРОВАНИЕ ПРИЛОЖЕНИЯ
 * - ЧТЕНИЕ СПИСКА РЕПОЗИТОРИЕВ ИЗ КОНФИНУРАЦИОННОГО ФАЙЛА
 * - ЗАПУСК ПОТОКА СИНХРОНИЗАЦИИ ДАННЫХ(ПОКА НЕ РЕАЛИЗОВАНО
 * - УПРАВЛЕНИЕ РЕПОЗИТОРИЯМИ
 */

// std stuff
#include <map>

// Qt stuff
#include <QString>
#include <QFile>
#include <QDomDocument>
#include <QTimer>
#include <QObject>

// our stuff
#include "systemtray.h"
#include "MVC/Model/model_repository.h"
#include "MVC/Model/model_icons.h"
#include "threadmodel.h"

class IRepository;

class FacadeApplication: public QObject
{
    Q_OBJECT

public:
    static FacadeApplication* getInstance();
    static void         RemoveInstance();
    ~FacadeApplication();

    /** @brief Модель для работы с потоками, содержащая переменные синхронизации */
    static ThreadModel  threadModel;

    /** @brief Методы-аксессоры системного трея для фасада, он создается извне */
    void                SetSystemTray(SystemTray* systemTray) { this->systemTray = systemTray; }   
    inline SystemTray*  GetSystemTray() const { return systemTray; }

    /** @brief Вернуть указатель на текущий репозиторий
    |details если нет активного репозитория, то возвращаем nullptr */
    IRepository*        GetCurrentRepository() const;

    /** @brief окончание клонирование репозитория
        @param successfully : true - клонирование завершилось удачно
                              false - клонирование завершилось неудачно
        @param information - если клонирование выполнено удачно, то название поддиректории,
        иначе причину ошибки
    */
    void                EndCloneRepository(const bool& successfully, const QString& information);

    /** @brief инициализация нового репозитория */
    void                InitNewRepository();

    // классы модели MVC объявим другом для нашего фасада
    // (принято такое архитектурное решение, что все методы фасада сделать приватными, и дать доступ только к моделям MVC,
    // т.к кроме модели никто не может уведомлять о новых событиях, действиях, происходящие на уровне представления)
    friend class GANN_MVC::ModelQmlAndCRepository;
    friend class GANN_MVC::ModelQmlAndCIcons;

private:
    FacadeApplication();
    FacadeApplication(const FacadeApplication& facade);
    FacadeApplication& operator = (const FacadeApplication& facade);
    static FacadeApplication* instance;

    void                InitClassCAndQML();

    /** @brief Загрузка репозиториев из сохраненных конфигов */
    void                LoadRepositories();

    /** @brief Сохранения нового репозитория в конфигах */
    void                SaveRepository(const QString& localURL, const QString& remoteURL, const QString& nameRepo,
                                       const bool autosync = true, const bool autosyncContent = true,
                                       const bool directMode = true) const;

    /** @brief Сохранения параметров репозитория в конфигах */
    void                SaveOptionsRepository(const QString &localURL);

    /** @brief Удаление репозитория из конфигов */
    void                DeleteRepository(const QString& localURL);

    /** @brief Запуск/Остановка демона просмотра(watch) за директориями у репозиториев */
    void                WatchRepositories(const bool start = true) const;

    /** @brief Запуск/Остановка демона просмотра(watch) у конкретного репозитория */
    void                WatchRepository(IRepository *repository, const bool start = true) const;

    /** @brief начать клонирование репозитория */
    GANN_DEFINE::RESULT_EXEC_PROCESS StartCloneRepository(QString& localURL, const QString& remoteURL, const QString& nameRepo);

    /** @brief Сменить итератор, указывающий на текущий репозиторий */
    void                ChangeCurrentRepository(const QString &dir);

    /** @brief Функция-слот, срабатывающий при тайм-ауте таймера синхронизации данных*/
    void                TimeOutTimeSync();

    /** @brief вектор зарегистрированных репозиториев */
    std::map<QString, std::unique_ptr<IRepository> > repository;
    /** @brief итератор на текущий репозиторий */
    std::map<QString, std::unique_ptr<IRepository> >::iterator currentRepository;

    /** @brief таймер синхронизации */
    QTimer              timeSync;

    /** @brief системный трей */
    SystemTray*         systemTray;

    /** @brief последнее сообщение об ошибке в клиенте */
    QString             lastError;

    /** @brief Возвращает путь к файлу конфигурации */
    const QString       GetPathToFileConfig() const;

    /** @brief Генерирует пустой файл конфигурации */
    void                GenerateEmptyFileConfig(const QString file) const;

    // временный репозиторий
    std::unique_ptr<IRepository> tempRepo;

signals:
    void                stopThreadIconsSync();


};

#endif // FACADEAPPLICATION_H
