#include "parsingcommandget.h"
#include "../analyze_execute_command/analyzeexecutecommandget.h"

#include <assert.h>

//  Qt stuff
#include <QJsonObject>
#include <QMap>

ParsingCommandGet::ParsingCommandGet(boost::shared_ptr<AnalyzeCommand::AnalyzeExecuteCommandGet> analyzeCommand) :
    IParsingCommandOut(analyzeCommand)
  , startGet(false)
  , analizeCommandGet(analyzeCommand)
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
                if(doc.object().value("file").toString() != lastJSONDocument.object().value("file").toString())
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
            if(IsEndMiniCommand(doc, ok))
            {
                // команда завершилась
                ok ? EndGetContentFile() : ErrorGetContentFile(doc);
            }
        }
    }
    else if(!commandStart && commandEnd)
    {
        // команда выполнилась
    }
}
//----------------------------------------------------------------------------------------/
void ParsingCommandGet::StartGetContentFile(const QJsonDocument &doc)
{
    assert(!startGet && "Предыдущий ресурс еще не скачался, и началось новое скачивание. Что то пошло не так!!!");
    startGet = true;

    nameFileGetContent = doc.object().value("file").toString();
    analizeCommandGet->StartGetContentFile(nameFileGetContent);
}
//----------------------------------------------------------------------------------------/
void ParsingCommandGet::EndGetContentFile()
{
    assert(startGet && "Скачивание ресурса не было запущено");
    startGet = false;
    analizeCommandGet->EndGetContentFile(nameFileGetContent);
}
//----------------------------------------------------------------------------------------/
void ParsingCommandGet::ErrorGetContentFile(const QJsonDocument &doc)
{
    assert(startGet && "Скачивание ресурса не было запущено");
    startGet = false;
    QMap<QString, QString> descriptionError;
    const QJsonObject& object = doc.object();
    auto it = object.find("note");
    if(it != object.end())
    {
//        descriptionError["reason"] = (*it).toString();
        descriptionError["reason"] = "not available";
    }
    else {
        descriptionError["reason"] = "";
    }

    analizeCommandGet->ErrorGetContentFile(nameFileGetContent, descriptionError);
}
//----------------------------------------------------------------------------------------/

