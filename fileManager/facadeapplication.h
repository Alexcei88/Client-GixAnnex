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
#include <vector>

// boost stuff
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

// Qt stuff
#include <QString>
#include <QFile>
#include <QDomDocument>

class FacadeApplication
{

public:
    static FacadeApplication* getInstance();

private:
    FacadeApplication();
    FacadeApplication(const FacadeApplication& facade);
    FacadeApplication& operator = (const FacadeApplication& facade);
    static boost::shared_ptr<FacadeApplication> instance;

    void            InitClassCAndQML();

    /** @brief загрузка репозиториев из сохраненных конфигов */
    void            LoadRepositories();

#warning PUBLIC_FIELD_CLASS
    // временно публичный
public:
    /** @brief сохранения репозитория в конфигах */
    void            SaveRepository(const QString& localURL, const QString& remoteURL, const QString& nameRepo);

    /** @brief файл конфигов репозитория, формат xml*/
    const QString   pathFileRepoConfig;

    QFile           fileRepoConfig;

};

#endif // FACADEAPPLICATION_H
