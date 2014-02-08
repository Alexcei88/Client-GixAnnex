#include "parsingcommanddirectmode.h"
#include "analyze_execute_command/analyzeexecutecommandchangedirectmode.h"
#include <assert.h>

//  Qt stuff
#include <QJsonObject>

ParsingCommandDirectMode::ParsingCommandDirectMode(boost::shared_ptr<AnalyzeCommand::AnalyzeExecuteCommandChangeDirectMode> analyzeCommand):
    IParsingCommandOut(analyzeCommand)
  , analizeCommandChangeMode(analyzeCommand)
{}
//----------------------------------------------------------------------------------------/
void ParsingCommandDirectMode::ParsingData()
{
    // команда стартовала, но еще не завершилась
    if(commandStart && !commandEnd)
    {

    }
    else if(!commandStart && commandEnd)
    {
        // команда завершилась
        if(lastJSONDocument.isNull())
        {
            analizeCommandChangeMode->ErrorChangeDirectMode();
        }
        else
        {
            QJsonObject object = lastJSONDocument.object();
            assert(object.take("file").toString("dffsdf") == "");
            bool ok;
            IsEndMiniCommand(lastJSONDocument, ok);
            if(!ok)
            {
                analizeCommandChangeMode->ErrorChangeDirectMode();
            }
            else
            {
                const bool mode = object.take("command").toString() == "direct";
                analizeCommandChangeMode->ChangeDirectMode(mode);
            }
        }
    }
}
//----------------------------------------------------------------------------------------/

