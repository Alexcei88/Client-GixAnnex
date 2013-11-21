#ifndef FACADEAPPLICATION_H
#define FACADEAPPLICATION_H

/*
 * КЛАСС-СИНГЛЕТОН, УПРАВЛЯЮЩИЙ ПРИЛОЖЕНИЕМ
 * В ЕГО ОТВЕТСТВЕННОСТЬ ВХОДИТ:
 * - КОНФИГУРИРОВАНИЕ ПРИЛОЖЕНИЯ
 * - ЧТЕНИЕ СПИСКА РЕПОЗИТОРИЕВ ИЗ КОНФИНУРАЦИОННОГО ФАЙЛА
 * - ЗАПУСК ПОТОКА СИНХРОНИЗАЦИИ СУЩЕСТВУЮЩИХ РЕПОЗИТОРИЕВ
 */

// std stuff
#include <map>

// boost stuff
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

// Qt stuff
#include <QString>
#include <QFile>
#include <QDomDocument>
#include <QTimer>

// our stuff
#include "systemtray.h"
#include "MVC/Model/model_repository.h"
#include "MVC/Model/model_icons.h"

class IRepository;

class FacadeApplication
{

public:
    static FacadeApplication* getInstance();
    void            SetSystemTray(SystemTray* systemTray) { this->systemTray = systemTray; }

    // классы модели MVC объявим другом для нашего фасада(
    // принято такое архитектурное решение, что все методы фасада сделать приватными, и дать доступ только к моделям MVC,
    // т.к кроме модели никто не может уведомлять о новых событиях, действиях, происходящие на уровне представления)
    friend class GANN_MVC::ModelQmlAndCRepository;
    friend class GANN_MVC::ModelQmlAndCIcons;

private:
    FacadeApplication();
    FacadeApplication(const FacadeApplication& facade);
    FacadeApplication& operator = (const FacadeApplication& facade);
    static boost::shared_ptr<FacadeApplication> instance;

    void                InitClassCAndQML();

    /** @brief Загрузка репозиториев из сохраненных конфигов */
    void                LoadRepositories();

    /** @brief Сохранения репозитория в конфигах */
    void                SaveRepository(const QString& localURL, const QString& remoteURL, const QString& nameRepo,
                                       const bool autosync = true, const bool autosyncContent = true
                                       );

    /** @brief Запуск демона просмотра(watch) за директориями у репозиториев */
    void                StartWatchRepositories() const;

    /** @brief Запуск демона просмотра(watch) у конкретного репозитория */
    void                StartWatchRepository(const IRepository* repository) const;

    /** @brief начать клонирование репозитория */
    GANN_DEFINE::RESULT_EXEC_PROCESS StartCloneRepository(QString& localURL, const QString& remoteURL, const QString& nameRepo);

    /** @brief Сменить итератор текущий репозиторий */
    void                ChangeCurrentRepository(const QString &dir);

    /** @brief Функция-слот, срабатывающий при тайм-айте таймера синхронизации данных*/
    void                TimeOutTimeSync();

    /** @brief путь к файлу конфигов репозитория, формат xml */
    const QString       pathFileRepoConfig;
    /** @brief вектор репозиториев, хранящиеся на клиенте */
    std::map<QString, std::unique_ptr<IRepository> > repository;
    /** @brief итератор на текущий репозиторий */
    std::map<QString, std::unique_ptr<IRepository> >::iterator currentRepository;

    /** @brief таймер, отвественный за синхронизацию контента с другими репозиториями */
    QTimer              timeSync;

    /** @brief системный трей */
    SystemTray*         systemTray;
    QFile               fileRepoConfig;

    /** @brief последнее сообщение об ошибке в клиенте */
    QString             lastError;

};

#endif // FACADEAPPLICATION_H
