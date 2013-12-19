#include "parsingcommandget.h"
#include "../repository/irepository.h"
#include <assert.h>

//  Qt stuff
#include <QJsonObject>

ParsingCommandGet::ParsingCommandGet(IRepository* repository) :
    IParsingCommandOut(repository)
  , startGet(false)
{}
//----------------------------------------------------------------------------------------/
void ParsingCommandGet::ParsingData()
{
    // команда стартовала, но еще не завершилась
    if(commandStart && !commandEnd)
    {
        for(std::vector<QJsonDocument>::iterator it = arrayJSONDocument.begin(); it != arrayJSONDocument.end(); ++it)
        {
            const QJsonDocument& doc = (*it);
            if(!lastJSONDocument.isNull())
            {
                if(doc.object().take("file").toString() != lastJSONDocument.object().take("file").toString())
                {
                    // документ не был в обработке, запускаем
                    StartGetContentFile(doc);
                }
            }
            else
            {
                StartGetContentFile(doc);
            }
            bool ok = false;
            if(IsEndCommand(doc, ok))
            {
                // команда завершилась
                ok ? EndGetContentFile() : ErrorGetContentFile(doc);
            }
        }
    }
    else if(!commandStart && commandEnd)
    {
        // команда завершилась
    }
}
//----------------------------------------------------------------------------------------/
void ParsingCommandGet::StartGetContentFile(const QJsonDocument &doc)
{
    assert(!startGet && "Предыдущий ресурс еще не скачался, и началось новое скачивание. Что то пошло не так!!!");
    startGet = true;

    nameFileGetContent = doc.object().take("file").toString();
    emit repository->startGetContentFile(nameFileGetContent);
}
//----------------------------------------------------------------------------------------/
void ParsingCommandGet::EndGetContentFile()
{
    assert(startGet && "Скачивание ресурса не было запущено");
    startGet = false;
    emit repository->endGetContentFile(nameFileGetContent);
}
//----------------------------------------------------------------------------------------/
void ParsingCommandGet::ErrorGetContentFile(const QJsonDocument &doc)
{
    assert(startGet && "Скачивание ресурса не было запущено");
    startGet = false;
    emit repository->errorGetContentFile(nameFileGetContent, "ffff");
}
//----------------------------------------------------------------------------------------/

