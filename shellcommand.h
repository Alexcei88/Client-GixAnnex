#ifndef SHELLCOMMAND_H
#define SHELLCOMMAND_H

#include "tshell.h"

class ShellCommand
{
public:
    ShellCommand();

    // 1. Инициализация репозитория
    int         InitRepositories(const QString& nameRepo);
    // 2. Добавление каталога/файла в репозиторий
    int         AddFile(const QString& path);
    // 3. закачать контент у файлов((директории)
    int         GetContentFile(const QString& path);
    // 4. удалить контент у файлов((директории)
    int         DropContentFile(const QString& path);
    // 5. Удалить файл(директорию) из репозитория вместе с контентом
    int         RemoveFile(const QString& path);
    // 6. Синхронизация с главным репозиторием
    int         Sync();
    // 7. оказывает местонахождение файла в других репозиториях
    int         WhereisFiles(const QString& path, QString& result);

private:
    boost::shared_ptr<TShell> shell;
    const QString& baseCommand;
};

#endif // SHELLCOMMAND_H
