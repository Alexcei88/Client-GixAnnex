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

// our stuff
#include "systemtray.h"
#include "repository/irepository.h"

class IRepository;

class FacadeApplication
{

public:
    static FacadeApplication* getInstance();
    void            SetSystemTray(SystemTray* systemTray) { this->systemTray = systemTray; };

    // класс модели MVC объявим другом
    friend class ModelQmlAndCRepository;
private:
    FacadeApplication();
    FacadeApplication(const FacadeApplication& facade);
    FacadeApplication& operator = (const FacadeApplication& facade);
    static boost::shared_ptr<FacadeApplication> instance;

    void            InitClassCAndQML();
#warning PUBLIC_FIELD_CLASS
    // временно публичный
public:
    /** @brief загрузка репозиториев из сохраненных конфигов */
    void            LoadRepositories();

    /** @brief сохранения репозитория в конфигах */
    void            SaveRepository(const QString& localURL, const QString& remoteURL, const QString& nameRepo);

    /** @brief начать клонирование репозитория */
    GANN_DEFINE::RESULT_EXEC_PROCESS StartCloneRepository(const QString& localURL, const QString& remoteURL, const QString& nameRepo);

    /** @brief закрытие окна клонирования
    @param 1 - прерывание команды
           0 - просто закрыть окно
    */
    void            CancelCloneRepository(const bool breakCommand = false);

    /** @brief перезагрузить модель со списком репозиториев*/
    bool            ReLoadListRepository() const;




    /** @brief путь к файлу конфигов репозитория, формат xml */
    const QString   pathFileRepoConfig;

    QFile           fileRepoConfig;

    /** @brief вектор репозиториев, хранящиеся на клиенте */
    std::map<QString, boost::shared_ptr<IRepository>> repository;

    /** @brief системный трей */
    SystemTray*     systemTray;

};

#endif // FACADEAPPLICATION_H
