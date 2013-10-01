#ifndef IREPOSITORY_H
#define IREPOSITORY_H

#include "../shell/shellcommand.h"

class IRepository
{
public:

    IRepository();
    IRepository(const QString& localUrl, const QString& remoteUrl, const QString& nameRepo);

    virtual ~IRepository() {};

    /**
    @brief установка параметров автосинхронизации
    @param autosync -
    @param autosyncContent -
    @return void
    */
    void                SetParamSyncRepository(const bool& autosync, const bool& autosyncContent);

    /** @brief взятие параметров автосинхронизации репозитория*/
    bool                GetParamSyncRepository() const { return paramSyncRepo.autosync; };
    bool                GetParamSyncContentRepository() const { return paramSyncRepo.autosyncContent; };


    /**
    @brief клонирование репозитория
    @param localURL -
    @param nameRepo -
    @param remoteURL - адрес репозитория, откуда копируем
    @return 0 - нет ошибок
    */
    virtual GANN_DEFINE::RESULT_EXEC_PROCESS CloneRepository(QString& localURL, const QString& nameRepo, const QString& remoteURL) = 0;

    /**
    @brief удаление репозитория
    @param localURL -
    @return 0 - нет ошибок
    */
    virtual GANN_DEFINE::RESULT_EXEC_PROCESS DeleteRepository(const QString& localURL) = 0;

    /**
    @brief получение контента у файла из репозитория
    @param file - имя файла(папки) назначения
    @return 0 - нет ошибок
    */
    virtual GANN_DEFINE::RESULT_EXEC_PROCESS GetContentFile(const QString& file = " ") const = 0;

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

    } ParamContentFile;


protected:
    boost::shared_ptr<ShellCommand> shellCommand;

    // удаленный адрес репозитория
    QString         remoteURL;
    // локальный адрес репозитория
    QString         localURL;
    // название репозитория Git-Annex
    QString         nameRepo;

private:
    void            InitClass();

    ParamRepository paramSyncRepo;

};

#endif // IREPOSITORY_H
