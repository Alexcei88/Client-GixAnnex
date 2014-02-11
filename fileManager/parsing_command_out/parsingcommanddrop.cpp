#include "parsingcommanddrop.h"
#include "../analyze_execute_command/analyzeexecutecommanddrop.h"

#include <assert.h>
//  Qt stuff
#include <QJsonObject>

ParsingCommandDrop::ParsingCommandDrop(boost::shared_ptr<AnalyzeCommand::AnalyzeExecuteCommandDrop> analyzeCommand) :
    IParsingCommandOut(analyzeCommand)
  , startDrop(false)
  , analizeCommandDrop(analyzeCommand)
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
            if(IsEndMiniCommand(doc, ok))
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
    analizeCommandDrop->StartDropContentFile(nameFileGetContent);
}
//----------------------------------------------------------------------------------------/
void ParsingCommandDrop::EndDropContentFile()
{
    assert(startDrop && "Удаление ресурса не было запущено");
    startDrop = false;
    analizeCommandDrop->EndDropContentFile(nameFileGetContent);
}
//----------------------------------------------------------------------------------------/
void ParsingCommandDrop::ErrorDropContentFile(const QJsonDocument &doc)
{
    assert(startDrop && "Удаление ресурса не было запущено");
    startDrop = false;
    Q_UNUSED(doc);
    analizeCommandDrop->ErrorDropContentFile(nameFileGetContent, "Error");
}
//----------------------------------------------------------------------------------------/
