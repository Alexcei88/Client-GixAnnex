#include "parsingcommandinfo.h"
#include "analyze_execute_command/analizeexecutecommandinfo.h"

//  Qt stuff
#include <QJsonObject>
#include <QMap>
#include <QString>
#include <QVector>

//----------------------------------------------------------------------------------------/
ParsingCommandInfo::ParsingCommandInfo(boost::shared_ptr<AnalyzeCommand::AnalizeExecuteCommandInfo> analyzeCommand) :
    IParsingCommandOut(analyzeCommand)
  , analizeCommandInfo(analyzeCommand)
{}
//----------------------------------------------------------------------------------------/
void ParsingCommandInfo::ParsingData()
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
            assert("команда Info не верно пропарсилась " && 0);
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
                analizeCommandInfo->SetInfoRepository(map);
            }
            else
            {
                // неудачно
                analizeCommandInfo->WasErrorGetInfoRepository();
            }
        }
        else
        {
            assert("команда Info не верно пропарсилась" && 0);
        }
    }
}
//----------------------------------------------------------------------------------------/

