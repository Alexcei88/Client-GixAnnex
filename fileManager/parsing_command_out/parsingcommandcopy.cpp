#include "parsingcommandcopy.h"
#include "../analyze_execute_command/analyzeexecutecommandcopy.h"
#include <assert.h>
//  Qt stuff
#include <QJsonObject>

//----------------------------------------------------------------------------------------/
//----------------------------------------------------------------------------------------/
ParsingCommandCopy::ParsingCommandCopy(boost::shared_ptr<AnalyzeCommand::AnalyzeExecuteCommandCopy> analyzeCommand) :
    IParsingCommandOut(analyzeCommand)
  , startCopy(false)
  , analizeCommandCopy(analyzeCommand)
{}
//----------------------------------------------------------------------------------------/
void ParsingCommandCopy::ParsingData()
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
                    StartCopyContentFile(doc);
                }
            }
            else
            {
                StartCopyContentFile(doc);
            }
            bool ok = false;
            if(IsEndMiniCommand(doc, ok))
            {
                // команда завершилась
                ok ? EndCopyContentFile() : ErrorCopyContentFile(doc);
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
void ParsingCommandCopy::StartCopyContentFile(const QJsonDocument &doc)
{
    assert(!startCopy && "Предыдущий ресурс еще не скопировался, и началось новое копирование. Что то пошло не так!!!");
    startCopy = true;
    nameFileGetContent = doc.object().value("file").toString();
    analizeCommandCopy->StartCopyContentFile(nameFileGetContent);
}
//----------------------------------------------------------------------------------------/
void ParsingCommandCopy::EndCopyContentFile()
{
    assert(startCopy && "Копирование ресурса не было запущено");
    startCopy = false;
    analizeCommandCopy->EndCopyContentFile(nameFileGetContent);
}
//----------------------------------------------------------------------------------------/
void ParsingCommandCopy::ErrorCopyContentFile(const QJsonDocument &doc)
{
    assert(startCopy && "Удаление ресурса не было запущено");
    startCopy = false;
    Q_UNUSED(doc);
    analizeCommandCopy->ErrorCopyContentFile(nameFileGetContent, "Error");
}
//----------------------------------------------------------------------------------------/
