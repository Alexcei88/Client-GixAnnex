#ifndef PARSINGCOMMANDGET_H
#define PARSINGCOMMANDGET_H

#include "iparsingcommandout.h"

// Qt stuff
#include <QString>
#include <QJsonArray>

class ParsingCommandGet : public IParsingCommandOut
{
public:
    ParsingCommandGet(IRepository* repository);
    virtual void        ParsingData();

private:
    // флаг начала скачивания ресурсов
    bool                startGet;
    // имя текущего скачиваемого ресурса
    QString             nameFileGetContent;
    //  начала скачивания файла
    void                StartGetContentFile(const QJsonDocument& doc);
    // конец скачивания файла
    void                EndGetContentFile();
    // скачивание файла завершилось с ошибкой
    void                ErrorGetContentFile(const QJsonDocument &doc);

};

#endif // PARSINGCOMMANDGET_H
