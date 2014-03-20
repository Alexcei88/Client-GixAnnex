#pragma once

#include <QVariantList>

#include <map>
#include "../define.h"
#include "../repository/irepository.h"

namespace GANN_MVC
{

class ModelQmlAndCRepository
{
public:
    ModelQmlAndCRepository();

    /** @brief Получить дефалтный репозиторий */
    const QString       GetDefaultRepository() const;

    /** @brief Берет состояние репозитория */
    const QString       GetStateRepository(const QString& path) const;

    /** @brief Удаление репозитория */
    void                DeleteRepository(const QString &path) const;

    /** @brief включает/выключает синхронизацию текущего репозитория */
    void                SetEnableRepository(bool enable);

    /** @brief есть ли команды у текущего репозитория */
    bool                IsExecuteCommandForCurrentRepository() const;

    /** @brief Клонировать репозиторий */
    GANN_DEFINE::RESULT_EXEC_PROCESS CloneRepository(const QString& localUlr, const QString& remoteURL, const QString& nameRepo);

    /** @brief Остановить клонирование */
    void                CancelCloneRepository(const bool breakCommand = true) const;

    /** @brief Взять контент у файла(директории)*/
    GANN_DEFINE::RESULT_EXEC_PROCESS GetContentDirectory(const QString& dir) const;

    /** @brief Удалить контент у файла(директории)*/
    GANN_DEFINE::RESULT_EXEC_PROCESS DropContentDirectory(const QString& dir) const;

    /** @brief Удалить файл(директорию) из репозитория */
    GANN_DEFINE::RESULT_EXEC_PROCESS RemoveDirectory(const QString& dir) const;

    /** @brief Сменить текущий репозиторий */
    void                ChangeCurrentRepository(const QString &dir) const;

    /** @brief Смена текущей отображаемой директории */
    void                ChangeCurrentViewDirectory(const QString &dir) const;

    /** @brief Вернуть массив параметров состояний синхронизации файлов и директории */
    const QMap<QString, IRepository::PARAMETR_FILEFOLDER_GIT_ANNEX>& GetParamSyncFileDir() const;

    /** @brief Дата посл модификации файла */
    const QString       GetLastModifiedFile(const QString &file);
    /** @brief Размер файла */
    const QString       GetSizeFile(const QString &file);

    /** @brief Является ли выбранный путь поддиректорией корневого пути репозитория */
    bool                DirIsSubRootDirRepository(const QString& dir) const;

    /** @brief возвращает полный путь до файла конфигурации */
    const QString GetFullPathFileConfigRepositories() const;

private:
    // в качестве служебных целей
    QFileInfo           fileInfo;
    // текущее соединение с классом выполнения команд
    mutable QMetaObject::Connection connectionFacadeShellCommand;
    // состояние, в которое перейдет репозиторий по истечении выполнения команды
    bool                willEnableRepository;


private slots:
    /** @brief изменяет режим синхронизации текущего репозитория */
    void                ChangeEnabledRepository(const bool enable, const bool hideWaitWindow = false) const;
};

}
