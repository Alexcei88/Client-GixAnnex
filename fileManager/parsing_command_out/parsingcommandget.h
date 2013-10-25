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
    //  начала скачивания файла
    void                StartGetContentFile();
    // конец скачивания файла
    void                EndGetContentFile();
};

#endif // PARSINGCOMMANDGET_H
