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
#include "repository/irepository.h"

class IRepository;

class FacadeApplication
{

public:
    static FacadeApplication* getInstance();
    void            SetSystemTray(SystemTray* systemTray) { this->systemTray = systemTray; };

    // класс модели MVC объявим другом
    friend class GANN_MVC::ModelQmlAndCRepository;

private:
    FacadeApplication();
    FacadeApplication(const FacadeApplication& facade);
    FacadeApplication& operator = (const FacadeApplication& facade);
    static boost::shared_ptr<FacadeApplication> instance;

    void            InitClassCAndQML();

    /** @brief загрузка репозиториев из сохраненных конфигов */
    void            LoadRepositories();

    /** @brief сохранения репозитория в конфигах */
    void            SaveRepository(const QString& localURL, const QString& remoteURL, const QString& nameRepo);

    /** @brief начать клонирование репозитория */
    GANN_DEFINE::RESULT_EXEC_PROCESS StartCloneRepository(QString& localURL, const QString& remoteURL, const QString& nameRepo);

    /** @brief Сменить итератор текущий репозиторий */
    void            ChangeCurrentRepository(const QString &dir);

    /** @brief Слот, срабатывающий при тайм-айте таймера(в основном синхронизация данных)*/
    void            TimeOutTimeSync();


    /** @brief путь к файлу конфигов репозитория, формат xml */
    const QString   pathFileRepoConfig;
    /** @brief вектор репозиториев, хранящиеся на клиенте */
    std::map<QString, boost::shared_ptr<IRepository> > repository;
    /** @brief итератор на текущий репозиторий */
    std::map<QString, boost::shared_ptr<IRepository> >::iterator currentRepository;

    /** @brief таймер, отвественный за синхронизацию контента с другими репозиториями */
    QTimer          timeSync;

    /** @brief системный трей */
    SystemTray*     systemTray;
    QFile           fileRepoConfig;




};

#endif // FACADEAPPLICATION_H
