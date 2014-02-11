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
#include <QFileSystemWatcher>

namespace AnalyzeCommand
{
    class FacadeAnalyzeCommand;
}

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
            Synced,             // синхронизация включена и выполнена
            SyncedError,        // при синхронизации была ошибка
            Disable_sincing     // синхронизация выключена
    };

    // состояния файла
    enum STATE_FILE_AND_DIR
    {
         SyncingF = 0        // идет синхронизация
        ,SyncedF             // синхронизация выполнена
        ,SyncedFError        // при синхронизации была ошибка
        ,Disable_sincingF    // синхронизация выключена
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
        // режим работы репозитория(прямой, косвенный)(true - прямой, false - косвенный)
        bool        directMode;
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
    void                 SetParamSyncRepository(const bool& autosync, const bool& autosyncContent);

    /** @brief взятие параметров автосинхронизации репозитория */
    inline bool          GetParamSyncRepository() const { return paramRepo.autosync; }
    inline bool          GetParamSyncContentRepository() const { return paramRepo.autosyncContent; }

    /** @brief Возвращает локальный путь, по которому храниться репозиторий */
    inline QString       GetLocalURL() const { return localURL; }
    /** @brief Возвращает удаленный путь, откуда скачан репозиторий */
    inline QString       GetRemoteURL() const { return remoteURL; }
    /** @brief Возвращает имя репозитория */
    inline QString       GetNameRepo() const { return nameRepo; }

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
    @param mode - режим вызова функции получения контента(true - автоматический, false - пользовательский)
    @return 0 - нет ошибок
    */
    virtual GANN_DEFINE::RESULT_EXEC_PROCESS GetContentFile(const QString& file = " ", const bool mode = false) = 0;

    /**
    @brief удаление контента у файла из репозитория
    @param file - имя файла(папки) назначения
    @return 0 - нет ошибок
    */
    virtual GANN_DEFINE::RESULT_EXEC_PROCESS DropContentFile(const QString& file = " ", const bool mode = false) = 0;

    /**
    @brief удалить файл из репозитория
    @param file - имя файла(папки) назначения
    @return 0 - нет ошибок
    */
    virtual GANN_DEFINE::RESULT_EXEC_PROCESS RemoveFile(const QString& file = " ") = 0;

    /**
    @brief получение информации, в каких репозиториях находиться файл
    @param file - имя файла(папки) назначения
    @return 0 - нет ошибок
    */
    virtual GANN_DEFINE::RESULT_EXEC_PROCESS WhereisFile(const QString& file = " ") = 0;

    /**
    @brief синхронизация с удаленным репозиторием
    */
    virtual GANN_DEFINE::RESULT_EXEC_PROCESS SyncRepository() const = 0;

    /**
    @brief запуск демона просмотра за рабочей директорией репозитория
    */
    virtual GANN_DEFINE::RESULT_EXEC_PROCESS StartWatchRepository();

    /**
    @brief остановка демона просмотра за рабочей директорией репозитория
    */
    virtual GANN_DEFINE::RESULT_EXEC_PROCESS StopWatchRepository();

    /**
    @brief перевод репозитория в прямой/косвенный режим
    */
    virtual GANN_DEFINE::RESULT_EXEC_PROCESS SetDirectMode(const bool& direct);

    /**
    @brief Взять состояние, в котором находиться репозиторий
    */
    bool                GetDirectMode() const { return paramRepo.directMode; }


    /** @brief Установка состояния репозитория */
    void                SetState(const STATE_REPOSITORY& state);

    /** @brief Взятие состояния репозитория */
    QString             GetState() const;

    /**
    @brief Взятие состояния синхронизации у конкретного файла(директории)
    @param fileDirName - название файла(директории), у которого берем состояние
    */
    QString             GetStateFileDir(const QString& fileDirName) const;

    /**
    @brief Взятие состояния у всех файлов в текущей директории
    @return возвращаем константную ссылку на защищенное поле класса
    */
    inline const QMap<QString, PARAMETR_FILEFOLDER_GIT_ANNEX>& GetStateFileDir() const { return paramSyncFileDir; };

    /** @brief Изменение  рабочей директории */
    void                ChangeCurrentDirectory(const QString& curDir);

    /** @brief Обновить параметры синхронизации у текущей директории
        Функция дергается из потока синхронизации иконок, чтобы получить последние параметры синхронизации
    */
    void                UpdateParamSyncFileDir();

    /** @brief Является ли выбранный путь поддиректорией корневого пути репозитория */
    bool                DirIsSubRootDirRepository(const QString& dir) const;

    /** @brief возвращает последнее сообщение об ошибке */
    const QString&      GetLastError() const { return lastError; };

    //====================================================================================/
    // ФУНКЦИИ-ОТВЕТЫ РЕПОЗИТОРИЯ НА ВЫПОЛНЕНИЕ КОМАНД
    //====================================================================================/
    /** @brief  удачное/неудачное клонирование репозитория */
    void                OnErrorCloneRepository(const QString& error);
    void                OnSuccessfullyCloneRepository(const QString&folder);

    /** @brief смена режима доступа репозитория(прямого/обратного) */
    void                OnChangeDirectMode(const bool mode);
    void                OnErrorChangeDirectMode(const QString& error);

protected:

    /** @brief Установка состояния у файла(или директории)
    @param fileDirName - название файла(директории), у которого меняем состояние */
    void                SetStateFileDir(const QString& fileDirName, const STATE_FILE_AND_DIR& state);

    boost::shared_ptr<ShellCommand> shellCommand;

    /** @brief Фасад системы анализа хода выполнения команд */
    boost::shared_ptr<AnalyzeCommand::FacadeAnalyzeCommand> facadeAnalyzeCommand;

    /** @brief удаленный адрес репозитория */
    QString             remoteURL;
    /** @brief локальный адрес репозитория */
    QString             localURL;
    /** @brief название репозитория Git-Annex */
    QString             nameRepo;

    // параметры репозитория
    PARAMETR_REPOSITORY_GI_ANNEX paramRepo;

    // перечисление состояний репозитория, в которых мы находимся
    // репозитория в целом
    QMetaEnum           metaEnumState;
    // конкретного файла
    QMetaEnum           metaEnumStateF;

    // параметры состояния файлов, в которых находиться текущий файл(или директория)
    QMap<QString, PARAMETR_FILEFOLDER_GIT_ANNEX> paramSyncFileDir;

    // вспом класс для манипулированием файловой системой
    QDir                dir;

    /** @brief последнее сообщение об ошибке в репозитории */
    QString             lastError;

    /** @brief watcher для слежения за директорией */
    QFileSystemWatcher  watcher;

private:
    void                InitClass();
    void                InitSignalAndSlots();

    /** @brief высчитать текущее состояние файла/директории */
    QString             CalculateStateFileDir(const QString& file) const;
    /** @brief получает список поддиректорий в корневой директории */
    void                GetListDirectoriesOnDirectory(const QString& path, QStringList& listDirectory);

private slots:
    // изменения в директории слежения за репой(нужно делать sync)
    void                OnDirectoryChanged(const QString& path);
    void                OnFileChanged(const QString& path);

signals:
    // неудачное клонирование
    void                errorCloneRepository(const QString&);

};

#endif // IREPOSITORY_H
