#ifndef SHELLCOMMAND_H
#define SHELLCOMMAND_H

#include "tshell.h"

// Qt stuff
#include <QRunnable>
#include <QThreadPool>

class IRepository;

namespace AnalyzeCommand
{
    class AnalyzeExecuteCommand;
}

class ShellCommand
{
public:
    ShellCommand();
    ~ShellCommand();

    // 1. Инициализация репозитория
    GANN_DEFINE::RESULT_EXEC_PROCESS InitRepositories(const QString& nameRepo);

    /**
     @brief SetWorkingDirectory - смена рабочего каталога
    */
    void                            SetWorkingDirectory(const QString &localURL);

    /**
    @brief Clone Repositories - клонирование репозитория
    @param folderClone - папка, куда будет скопирован репозиторий
    @return 0 - нет ошибок
    */
    GANN_DEFINE::RESULT_EXEC_PROCESS CloneRepositories(const QString& remoteURL, QString &folderClone
                                                       ,AnalyzeCommand::AnalyzeExecuteCommand *analize);

    /** @brief запустить/остановить демон просмотра за рабочей директорией
        @param start - true - запускает службу, false - останавливаем службу
    */
    GANN_DEFINE::RESULT_EXEC_PROCESS WatchRepository(const QString& path, const bool start = true) const;

    // 2. Добавление каталога/файла в репозиторий
    GANN_DEFINE::RESULT_EXEC_PROCESS AddFile(const QString& path) const;
    // 3. закачать контент у файлов((директории)
    GANN_DEFINE::RESULT_EXEC_PROCESS GetContentFile(const QString& path, IRepository* repository) const;
    // 4. удалить контент у файлов((директории)
    GANN_DEFINE::RESULT_EXEC_PROCESS DropContentFile(const QString& path, IRepository* repository) const;
    // 5. Удалить файл(директорию) из репозитория вместе с контентом
    GANN_DEFINE::RESULT_EXEC_PROCESS RemoveFile(const QString& path, const bool recursive = false) const;
    // 6. Синхронизация с главным репозиторием
    GANN_DEFINE::RESULT_EXEC_PROCESS Sync() const;
    // 7. оказывает местонахождение файла в других репозиториях
    GANN_DEFINE::RESULT_EXEC_PROCESS WhereisFiles(const QString& path, IRepository *repository) const;
    /** @brief установка прямого/косвенного режима работы репозитория */
    GANN_DEFINE::RESULT_EXEC_PROCESS SetDirectMode(const bool &direct, IRepository *repository) const;

    inline const QString getStrCommand() const { return strCommand; }
    inline const QString getLocalURL() const { return localURL; }

private:
    const QString   baseCommand;

    /** @brief команда, которая выполняется */
    QString         strCommand;
    /** @brief путь, откуда запускаеться shell */
    QString         localURL;

};

#endif // SHELLCOMMAND_H
