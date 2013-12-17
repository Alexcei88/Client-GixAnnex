#ifndef PARSINGCOMMANDDROP_H
#define PARSINGCOMMANDDROP_H

#include "iparsingcommandout.h"

// Qt stuff
#include <QString>

class ParsingCommandDrop : public IParsingCommandOut
{
public:
    ParsingCommandDrop(IRepository* repository);
    virtual void        ParsingData();

private:
    // флаг окончания скачивания ресурсов
    bool                startDrop;
    // имя текущего удаляемого ресурса
    QString             nameFileGetContent;
    //  начала удаления файла
    void                StartDropContentFile();
    // конец удаления файла
    void                EndDropContentFile();
    // удаление файла завершилось с ошибкой
    void                ErrorDropContentFile();
};

#endif // PARSINGCOMMANDDROP_H
