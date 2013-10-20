#ifndef PARSINGCOMMANDGET_H
#define PARSINGCOMMANDGET_H

#include "iparsingcommandout.h"
#include "../repository/irepository.h"

// Qt stuff
#include <QString>

class ParsingCommandGet : public IParsingCommandOut
{
public:
    ParsingCommandGet(const TShell *shell1, IRepository* repository);
    virtual void        ParsingData();

private:
    IRepository*        repository;
    // флаг начала скачивания ресурсов
    bool                startGet;
    // имя текущего скачиваемого ресурса
    QString             nameFileGetContent;
};

#endif // PARSINGCOMMANDGET_H
