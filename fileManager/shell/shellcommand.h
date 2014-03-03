#ifndef SHELLCOMMAND_H
#define SHELLCOMMAND_H

#include "tshell.h"

#include <QList>
#include <QQueue>
class IRepository;

namespace AnalyzeCommand
{
    class FacadeAnalyzeCommand;  
}
class ShellTask;

class ShellCommand
{
public:
    ShellCommand();
    ~ShellCommand();

    /** @brief Инициализация нового репозитория git-annex */
    GANN_DEFINE::RESULT_EXEC_PROCESS InitRepositories(const QString& nameRepo, AnalyzeCommand::FacadeAnalyzeCommand *facade);

    /**
     @brief SetWorkingDirectory - смена рабочего каталога
    */
    void                            SetWorkingDirectory(const QString &localURL);

    /**
    @brief Clone Repositories - клонирование репозитория
    @param folderClone - папка, куда будет скопирован репозиторий
    @return 0 - нет ошибок
    */
    GANN_DEFINE::RESULT_EXEC_PROCESS CloneRepositories(const QString& remoteURL, const QString localURL, AnalyzeCommand::FacadeAnalyzeCommand* facade);

    /** @brief Запустить/остановить демон просмотра за рабочей директорией
        @param start - true - запускает службу, false - останавливаем службу
    */
    GANN_DEFINE::RESULT_EXEC_PROCESS WatchRepository(const QString& path, const bool start = true) const;

    /** @brief Добавление каталога/файла в репозиторий */
    GANN_DEFINE::RESULT_EXEC_PROCESS AddFile(const QString& path) const;

    /** @brief Закачать контент у файлов((директории)
        @param mode - режим вызова функции получения контента(true - автоматический, false - пользовательский)
    */
    GANN_DEFINE::RESULT_EXEC_PROCESS GetContentFile(const QString& path, AnalyzeCommand::FacadeAnalyzeCommand* facade, const bool mode) const;

    /** @brief Удалить контент у файлов((директории)
        @param mode - режим вызова функции удаления контента(true - автоматический, false - пользовательский)
    */
    GANN_DEFINE::RESULT_EXEC_PROCESS DropContentFile(const QString& path, AnalyzeCommand::FacadeAnalyzeCommand* facade, const bool mode) const;

    /** @brief  Удалить файл(директорию) из репозитория вместе с контентом
        @param mode - режим, в котором работает репозиторий(true - в режиме direct, false - иначе
    */
    GANN_DEFINE::RESULT_EXEC_PROCESS RemoveFile(const QString& path, const bool mode, const bool recursive = false) const;
    // 6. Синхронизация с главным репозиторием
    GANN_DEFINE::RESULT_EXEC_PROCESS Sync() const;
    // 7. оказывает местонахождение файла в других репозиториях
    GANN_DEFINE::RESULT_EXEC_PROCESS WhereisFiles(const QString& path, AnalyzeCommand::FacadeAnalyzeCommand* facade) const;

    /** @brief Установка прямого/косвенного режима работы репозитория */
    GANN_DEFINE::RESULT_EXEC_PROCESS SetDirectMode(const bool &direct, AnalyzeCommand::FacadeAnalyzeCommand* facade) const;

    /** @brief Поиск файлов в директории(узнаем файлы, у которых есть контент) */
    GANN_DEFINE::RESULT_EXEC_PROCESS FindFileInPath(const QString& path, AnalyzeCommand::FacadeAnalyzeCommand* facade) const;

    /** @brief Копирование файла на удаленный сервер */
    GANN_DEFINE::RESULT_EXEC_PROCESS CopyFileToOtherRepository(const QString& file, const QString& nameRepository = "origin");

    /** @brief Перемещение файла на удаленный сервер */
    GANN_DEFINE::RESULT_EXEC_PROCESS MoveFileToOtherRepository(const QString& file, const QString& nameRepository = "origin");

    inline const QString getLocalURL() const { return localURL; }

private:
    const QString   baseCommand;

    /** @brief путь, откуда запускаеться shell */
    QString         localURL;

};

#endif // SHELLCOMMAND_H
