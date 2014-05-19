#include "analizeexecutecommandinfo.h"
#include "facadeanalyzecommand.h"
#include "repository/irepository.h"
#include "preferencesapplication.h"

// Qt stuff
#include <QString>
#include <QList>

using namespace AnalyzeCommand;

//----------------------------------------------------------------------------------------/
AnalizeExecuteCommandInfo::AnalizeExecuteCommandInfo(FacadeAnalyzeCommand& facadeAnalizeCommand):
    AnalyzeExecuteCommand(facadeAnalizeCommand)
{}
//----------------------------------------------------------------------------------------/
void AnalizeExecuteCommandInfo::SetInfoRepository(const QVariantMap& values)
{
    // проверяем directMode
    QVariantMap::const_iterator itMode = values.find("repository mode");
    if(itMode != values.end())
    {
        const bool mode = itMode->toString() == "direct";
        const IRepository* repository = facadeAnalyzeCommand.GetRepository();

        if(mode != PreferencesApplication::GetInstance()->GetDirectMode())
        {
            facadeAnalyzeCommand.ReStartCommand("fff", QVariant(PreferencesApplication::GetInstance()->GetDirectMode()));
        }
        if(mode != repository->GetDirectMode())
        {
            facadeAnalyzeCommand.ChangeDirectMode(mode);
        }
    }
}
//----------------------------------------------------------------------------------------/
void AnalizeExecuteCommandInfo::WasErrorGetInfoRepository()
{

}
//----------------------------------------------------------------------------------------/
