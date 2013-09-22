#ifndef IREPOSITORY_H
#define IREPOSITORY_H

#include "../shell/shellcommand.h"

class IRepository
{
public:

    /**
    @brief Структура, описывающая параметры хранения файлов репозиторий
    */
    typedef struct PARAMETR_REPOSITORY_GI_ANNEX
    {
        // автосинхронизация с сервером
        bool autosync;
        // автосинхронизация контента репозитория
        bool autosyncContent;

    } ParamRepository;

    /**
    @brief Структура, описывающая параметры файла(папки), входящие в репозиторий
    */
    typedef struct PARAMETR_FILEFOLDER_GIT_ANNEX
    {
        // автосинхронизация контента
        bool autosync;

    } ParamSaveFile;

    IRepository() { shellCommand = boost::make_shared<ShellCommand>(); };
    virtual ~IRepository() {};

    /**
    @brief клонирование репозитория
    @param localURL -
    @param nameRepo -
    @param remoteURL - адрес репозитория, откуда копируем
    @return 0 - нет ошибок
    */
    virtual int         CloneRepository(const QString& localURL, const QString& nameRepo, const QString& remoteURL) = 0;

    /**
    @brief удаление репозитория
    @param localURL -
    @return 0 - нет ошибок
    */
    virtual int         DeleteRepository(const QString& localURL) = 0;

    /**
    @brief получение контента у файла из репозитория
    @param file - имя файла(папки) назначения
    @return 0 - нет ошибок
    */
    virtual int         GetContentFile(const QString& file = " ") const = 0;

    /**
    @brief удаление контента у файла из репозитория
    @param file - имя файла(папки) назначения
    @return 0 - нет ошибок
    */
    virtual int         DropContentFile(const QString& file = " ") const = 0;

    /**
    @brief получение информации, в каких репозиториях находиться файл
    @param file - имя файла(папки) назначения
    @return 0 - нет ошибок
    */
    virtual int         WhereisFile(const QString& file = " ") const = 0;

protected:
    boost::shared_ptr<ShellCommand> shellCommand;

    // удаленный адрес репозитория
    QString         remoteURL;
    // локальный адрес репозитория
    QString         localURL;
    // название репозитория Git-Annex
    QString         nameRepo;
};

#endif // IREPOSITORY_H
