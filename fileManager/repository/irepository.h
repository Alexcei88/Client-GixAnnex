#ifndef IREPOSITORY_H
#define IREPOSITORY_H

#include "../shell/shellcommand.h"

class IRepository
{
public:
    IRepository() { shellCommand = boost::make_shared<ShellCommand>(); };
    virtual ~IRepository() {};
    // 1. Клонирование репозитория
    virtual int     CloneRepository(const QString& localURL, const QString& nameRepo, const QString& remoteURL) = 0;
    // 2. Удаление репозитория
    virtual int     DeleteRepository(const QString& localURL) = 0;
    // 3.

protected:
    boost::shared_ptr<ShellCommand> shellCommand;
    // удаленный адрес репозитория
    QString         remoteURL;
    // локальный адрес репозитория
    QString         localURL;
    // название репозитория Git-Annex
    QString         nameRepo;
};

#endif // IREPOSITORY_H
