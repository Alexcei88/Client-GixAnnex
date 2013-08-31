#ifndef SHELLCOMMAND_H
#define SHELLCOMMAND_H

#include "tshell.h"

class ShellCommand
{
public:
    ShellCommand();

    // 1. Инициализация репозитория
    int InitRepositories(const QString& nameRepo);
    // 2. Добавление каталога/файла в репозиторий


private:
    boost::shared_ptr<TShell> shell;
    const QString& baseCommand;
};

#endif // SHELLCOMMAND_H
