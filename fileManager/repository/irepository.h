#ifndef IREPOSITORY_H
#define IREPOSITORY_H

#include "../shell/shellcommand.h"

// Qt stuff
#include <QObject>
#include <QMetaObject>
#include <QMetaEnum>
#include <QDir>
#include <QMap>
#include <QVector>
#include <QFileInfo>

class IRepository : public QObject
{
    Q_OBJECT
    Q_ENUMS(STATE_REPOSITORY)
    Q_ENUMS(STATE_FILE_AND_DIR)
public:

    // состояние репозитория
    enum STATE_REPOSITORY
    {
            Syncing = 0,        // идет синхронизация
            Synced = 1,         // синхронизация выполнена
            Disable_sincing = 2 // синхронизация выключена
    };

    // состояния файла
    enum STATE_FILE_AND_DIR
    {
        SyncingF = 0,        // идет синхронизация
        SyncedF = 1,         // синхронизация выполнена
        Disable_sincingF = 2 // синхронизация выключена
    };

    /**
    @brief Структура, описывающая параметры хранения файлов репозиторий
    */
    struct PARAMETR_REPOSITORY_GI_ANNEX
    {
        // автосинхронизация с сервером
        bool        autosync;
        // автосинхронизация контента репозитория
        bool        autosyncContent;
        // состояние, в котором щас находимся
        QString     currentState;
    };

    /**
    @brief Структура, описывающая параметры файла(папки), входящие в репозиторий
    */
    struct PARAMETR_FILEFOLDER_GIT_ANNEX
    {
        // автосинхронизация контента
        bool        autosync;
        // состояние синхронизации, в котором находиться текущий файл
        QString     currentState;
        // свойства файла(директории)
        QFileInfo   fileInfo;
    };

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

    /** @brief взятие параметров автосинхронизации репозитория */
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
    virtual GANN_DEFINE::RESULT_EXEC_PROCESS DeleteRepository() = 0;

    /**
    @brief получение контента у файла из репозитория
    @param file - имя файла(папки) назначения
    @return 0 - нет ошибок
    */
    virtual GANN_DEFINE::RESULT_EXEC_PROCESS GetContentFile(const QString& file = " ") = 0;

    /**
    @brief удаление контента у файла из репозитория
    @param file - имя файла(папки) назначения
    @return 0 - нет ошибок
    */
    virtual GANN_DEFINE::RESULT_EXEC_PROCESS DropContentFile(const QString& file = " ") = 0;

    /**
    @brief получение информации, в каких репозиториях находиться файл
    @param file - имя файла(папки) назначения
    @return 0 - нет ошибок
    */
    virtual GANN_DEFINE::RESULT_EXEC_PROCESS WhereisFile(const QString& file = " ") const = 0;

    /**
    @brief синхрнизация с удаленным репозиторием
    */
    virtual GANN_DEFINE::RESULT_EXEC_PROCESS SyncRepository() const = 0;

    /**
    @brief Установка состояния репозитория
    */
    void                SetState(const STATE_REPOSITORY& state);

    /**
    @brief Взятие состояния репозитория
    */
    QString             GetState() const;

    /**
    @brief Взятие состояния синхронизации у конкретного файла(директории)
    @param fileDirName - название файла(директории), у которого берем состояние
    */
    QString             GetStateFileDir(const QString& fileDirName) const;

    /**
    @brief Взятие состояния у всех файлов в текущей директории
    @return возвращаем константную ссылку на защищенное поле класса(для скорости, состояния файла часто анализируется)
    */
    inline const QMap<QString, PARAMETR_FILEFOLDER_GIT_ANNEX>& GetStateFileDir() const { return paramSyncFileDir; };

    /** @brief Получить полностью новые параметры синхронизации(при смене рабочей директории) */
    void                UpdateParamSyncFileDirFull(const QString& curDir);

    /** @brief Обновить параметры синхронизации у текущей директории */
    void                UpdateParamSyncFileDir();

    /** @brief Является ли выбранный путь поддиректорией корневого пути репозитория */
    bool                DirIsSubRootDirRepository(const QString& dir) const;

    /** @brief возвращает последнее сообщение об ошибке */
    const QString&      GetLastError() { return lastError; };

protected:

    /**
    @brief Установка состояния у файла(или директории)
    @param fileDirName - название файла(директории), у которого меняем состояние
    */
    void                SetStateFileDir(const QString& fileDirName, const STATE_FILE_AND_DIR& state);

    boost::shared_ptr<ShellCommand> shellCommand;

    // удаленный адрес репозитория
    QString             remoteURL;
    // локальный адрес репозитория
    QString             localURL;
    // название репозитория Git-Annex
    QString             nameRepo;
    // параметры синхронизации репозитория
    PARAMETR_REPOSITORY_GI_ANNEX paramSyncRepo;

    // перечисление состояний репозитория, в которых мы находимся
    QMetaEnum           metaEnumState;
    QMetaEnum           metaEnumStateF;

    // параметры состояния файлов, в которых находиться текущий файл(или директория)
    QMap<QString, PARAMETR_FILEFOLDER_GIT_ANNEX> paramSyncFileDir;

    // вспом класс для манипулированием файловой системой
    QDir                dir;

    /** @brief последнее сообщение об ошибке в репозитории */
    QString             lastError;

private:
    void                InitClass();
    // вектор, содержащий файлы, которые сейчас скачиваются(или дано задание на скачивание)
    QList<QString>      gettingContentFile;
    // вектор, содержащий файлы, которые сейчас удаляются(или дано задание на удаление)
    QList<QString>      droppingContentFile;

    /** @brief идет ли в текущей директории(или сам текущий файл) получение контента в текущий момент времени */
    bool                IsGettingContentFileDir(const QString& file);

    /** @brief идет ли в текущей директории(или сам текущий файл) удаление контента в текущий момент времени */
    bool                IsDroppingContentFileDir(const QString& file);

    /** @brief содержит ли директория файл в поддиректориях */
    bool                DirContainsFile(const QString& dir, const QString& file) const;

public slots:
    // слот, говорящий о начале получения контента у файла
    void                OnStartGetContentFile(const QString&);
    void                OnEndGetContentFile(const QString&);
    // начало/конец удаленич
    void                OnStartDropContentFile(const QString&);
    void                OnEndDropContentFile(const QString&);
    // неудачное клонирование репозитория
    void                OnErrorCloneRepository(const QString&);

signals:
    // сигналы начала/конца get
    void                startGetContentFile(const QString&);
    void                endGetContentFile(const QString&);
    void                startDropContentFile(const QString&);
    void                endDropContentFile(const QString&);
    void                errorCloneRepository(const QString&);

};

#endif // IREPOSITORY_H
