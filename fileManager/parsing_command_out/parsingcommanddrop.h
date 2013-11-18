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
    // флаг окончания скачивания ресурсов
    bool                startDrop;
    // имя текущего удаляемого ресурса
    QString             nameFileGetContent;
    //  начала удаления файла
    void                StartDropContentFile();
    // конец удаления файла
    void                EndDropContentFile();
};

#endif // PARSINGCOMMANDDROP_H
