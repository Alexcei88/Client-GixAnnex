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
    void                StartDropContentFile(const QJsonDocument& doc);
    // конец удаления файла
    void                EndDropContentFile();
    // удаление файла завершилось с ошибкой
    void                ErrorDropContentFile(const QJsonDocument &doc);
};

#endif // PARSINGCOMMANDDROP_H
