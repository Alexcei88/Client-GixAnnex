#ifndef SHELLCOMMAND_H
#define SHELLCOMMAND_H

#include "tshell.h"

class ShellCommand
{
public:
    ShellCommand();
    ~ShellCommand();

    // 1. Инициализация репозитория
    RESULT_EXEC_PROCESS InitRepositories(const QString& nameRepo);

    /**
     * @brief SetWorkingDirectory - переход в директорию, откуда запускаем команды
     * @return 0 - нет ошибок
     */
    RESULT_EXEC_PROCESS SetWorkingDirectory(const QString& localURL);

    /**
     * @brief Clone Repositories - клонирование репозитория
     * @param folderClone - папка, куда был скопирован репозиторий
     * @return 0 - нет ошибок
     */
    RESULT_EXEC_PROCESS CloneRepositories(const QString& remoteURL, QString &folderClone);

    // 2. Добавление каталога/файла в репозиторий
    RESULT_EXEC_PROCESS AddFile(const QString& path);
    // 3. закачать контент у файлов((директории)
    RESULT_EXEC_PROCESS GetContentFile(const QString& path);
    // 4. удалить контент у файлов((директории)
    RESULT_EXEC_PROCESS DropContentFile(const QString& path);
    // 5. Удалить файл(директорию) из репозитория вместе с контентом
    RESULT_EXEC_PROCESS RemoveFile(const QString& path);
    // 6. Синхронизация с главным репозиторием
    RESULT_EXEC_PROCESS Sync();
    // 7. оказывает местонахождение файла в других репозиториях
    RESULT_EXEC_PROCESS WhereisFiles(const QString& path, QString& result);

private:
    const TShell*  shell;
    const QString& baseCommand;
};

#endif // SHELLCOMMAND_H
