#include "analizeexecutecommandstatus.h"
#include "facadeanalyzecommand.h"
#include "repository/irepository.h"

// Qt stuff
#include <QString>
#include <QList>

using namespace AnalyzeCommand;

//----------------------------------------------------------------------------------------/
AnalizeExecuteCommandStatus::AnalizeExecuteCommandStatus(FacadeAnalyzeCommand& facadeAnalizeCommand):
    AnalyzeExecuteCommand(facadeAnalizeCommand)
{}
//----------------------------------------------------------------------------------------/
void AnalizeExecuteCommandStatus::SetStatusRepository(const QVariantMap& values)
{
    // проверяем directMode
    QVariantMap::const_iterator itMode = values.find("repository mode");
    if(itMode != values.end())
    {
        const bool mode = itMode->toString() == "direct";
        const IRepository* repository = facadeAnalyzeCommand.GetRepository();
        if(mode != repository->GetDirectMode())
        {
            facadeAnalyzeCommand.ChangeDirectMode(mode);
        }
    }
}
//----------------------------------------------------------------------------------------/
void AnalizeExecuteCommandStatus::WasErrorGetStatusRepository()
{

}
//----------------------------------------------------------------------------------------/
