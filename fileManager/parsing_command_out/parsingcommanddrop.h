#ifndef PARSINGCOMMANDDROP_H
#define PARSINGCOMMANDDROP_H

#include "iparsingcommandout.h"
#include "../repository/irepository.h"

// Qt stuff
#include <QString>

class ParsingCommandDrop : public IParsingCommandOut
{
public:
    ParsingCommandDrop(const TShell *shell1, IRepository* repository);
    virtual void        ParsingData();

private:
    IRepository*        repository;
    // флаг начала скачивания ресурсов
    bool                startGet;
    // имя текущего скачиваемого ресурса
    QString             nameFileGetContent;
};

#endif // PARSINGCOMMANDDROP_H
