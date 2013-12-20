#include "parsingcommanddrop.h"
#include <assert.h>
#include "../repository/irepository.h"

//  Qt stuff
#include <QJsonObject>

ParsingCommandDrop::ParsingCommandDrop(IRepository* repository) :
    IParsingCommandOut(repository)
  , startDrop(false)
{}
//----------------------------------------------------------------------------------------/
void ParsingCommandDrop::ParsingData()
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
                    StartDropContentFile(doc);
                }
            }
            else
            {
                StartDropContentFile(doc);
            }
            bool ok = false;
            if(IsEndCommand(doc, ok))
            {
                // команда завершилась
                ok ? EndDropContentFile() : ErrorDropContentFile(doc);
            }
        }
    }
    else if(!commandStart && commandEnd)
    {
        // команда завершилась
    }
    else
    {
        // ничего не делаем
    }
}
//----------------------------------------------------------------------------------------/
void ParsingCommandDrop::StartDropContentFile(const QJsonDocument &doc)
{
    assert(!startDrop && "Предыдущий ресурс еще не удалился, и началось новое удаление. Что то пошло не так!!!");
    startDrop = true;
    nameFileGetContent = doc.object().take("file").toString();
    emit repository->startDropContentFile(nameFileGetContent);
}
//----------------------------------------------------------------------------------------/
void ParsingCommandDrop::EndDropContentFile()
{
    assert(startDrop && "Удаление ресурса не было запущено");
    startDrop = false;
    emit repository->endDropContentFile(nameFileGetContent);
}
//----------------------------------------------------------------------------------------/
void ParsingCommandDrop::ErrorDropContentFile(const QJsonDocument &doc)
{
    assert(startDrop && "Удаление ресурса не было запущено");
    startDrop = false;
    emit repository->errorDropContentFile(nameFileGetContent, "Error");
}
//----------------------------------------------------------------------------------------/
