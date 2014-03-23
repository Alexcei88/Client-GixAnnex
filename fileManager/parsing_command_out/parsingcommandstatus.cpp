#include "parsingcommandstatus.h"
#include "analyze_execute_command/analizeexecutecommandstatus.h"

//  Qt stuff
#include <QJsonObject>
#include <QMap>
#include <QString>
#include <QVector>

//----------------------------------------------------------------------------------------/
ParsingCommandStatus::ParsingCommandStatus(boost::shared_ptr<AnalyzeCommand::AnalizeExecuteCommandStatus> analyzeCommand) :
    IParsingCommandOut(analyzeCommand)
  , analizeCommandStatus(analyzeCommand)
{}
//----------------------------------------------------------------------------------------/
void ParsingCommandStatus::ParsingData()
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
            assert("команда status не верно пропарсилась " && 0);
        }
        // команда завершилась
        QJsonObject object = lastJSONDocument.object();
        bool ok = false;
        if(IsEndMiniCommand(lastJSONDocument, ok))
        {
            // команда завершилась
            if(ok)
            {
                // удачно
                QVariantMap map = object.toVariantMap();
                analizeCommandStatus->SetStatusRepository(map);
            }
            else
            {
                // неудачно
                analizeCommandStatus->WasErrorGetStatusRepository();
            }
        }
        else
        {
            assert("команда status не верно пропарсилась" && 0);
        }
    }
}
//----------------------------------------------------------------------------------------/

