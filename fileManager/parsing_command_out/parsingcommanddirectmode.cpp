#include "parsingcommanddirectmode.h"
#include <assert.h>
#include "../repository/irepository.h"


//  Qt stuff
#include <QJsonObject>

ParsingCommandDirectMode::ParsingCommandDirectMode(boost::shared_ptr<AnalyzeCommand::AnalyzeExecuteCommand> analyzeCommand):
    IParsingCommandOut(analyzeCommand)
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
            //emit repository->errorChangeDirectMode("dffsdf");
        }
        else
        {
            QJsonObject object = lastJSONDocument.object();
            assert(object.take("file").toString("dffsdf") == "");
            bool ok;
            IsEndMiniCommand(lastJSONDocument, ok);
            if(!ok)
            {
                //emit repository->errorChangeDirectMode("undefined");
            }
            else
            {
                const bool mode = object.take("command").toString() == "direct";
                //emit repository->changeDirectMode(mode);
            }
        }
    }
}
//----------------------------------------------------------------------------------------/

