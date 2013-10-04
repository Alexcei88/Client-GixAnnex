#ifndef SHELLCOMMAND_H
#define SHELLCOMMAND_H

#include "tshell.h"

// Qt stuff
#include <QRunnable>
#include <QThreadPool>

class ShellCommand
{
public:
    ShellCommand();
    ~ShellCommand();

    // 1. Инициализация репозитория
    GANN_DEFINE::RESULT_EXEC_PROCESS InitRepositories(const QString& nameRepo, const TShell* shell);

    /**
     @brief SetWorkingDirectory - смена рабочего каталога
     @return 0 - нет ошибок
    */
    GANN_DEFINE::RESULT_EXEC_PROCESS SetWorkingDirectory(const QString& localURL, const TShell *shell);

    /**
    @brief Clone Repositories - клонирование репозитория
    @param folderClone - папка, куда будет скопирован репозиторий
    @return 0 - нет ошибок
    */
    GANN_DEFINE::RESULT_EXEC_PROCESS CloneRepositories(const QString& remoteURL, QString &folderClone, const boost::shared_ptr<TShell> shell);

    // 2. Добавление каталога/файла в репозиторий
    GANN_DEFINE::RESULT_EXEC_PROCESS AddFile(const QString& path, const boost::shared_ptr<TShell> shell) const;
    // 3. закачать контент у файлов((директории)
    GANN_DEFINE::RESULT_EXEC_PROCESS GetContentFile(const QString& path, const boost::shared_ptr<TShell> shell) const;
    // 4. удалить контент у файлов((директории)
    GANN_DEFINE::RESULT_EXEC_PROCESS DropContentFile(const QString& path, const boost::shared_ptr<TShell> shell) const;
    // 5. Удалить файл(директорию) из репозитория вместе с контентом
    GANN_DEFINE::RESULT_EXEC_PROCESS RemoveFile(const QString& path, const boost::shared_ptr<TShell> shell) const;
    // 6. Синхронизация с главным репозиторием
    GANN_DEFINE::RESULT_EXEC_PROCESS Sync(const boost::shared_ptr<TShell> shell) const;
    // 7. оказывает местонахождение файла в других репозиториях
    GANN_DEFINE::RESULT_EXEC_PROCESS WhereisFiles(const QString& path, const boost::shared_ptr<TShell> shell) const;

    /**
    @brief Pull Repositories - послать изменения в удаленный репозитрий
    @return 0 - нет ошибок
    */
    GANN_DEFINE::RESULT_EXEC_PROCESS PullRepositories(const boost::shared_ptr<TShell> shell) const;

private:
    const QString  baseCommand;

};

#endif // SHELLCOMMAND_H
