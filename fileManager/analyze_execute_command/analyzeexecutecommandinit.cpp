#include "analyzeexecutecommandinit.h"
#include "facadeanalyzecommand.h"

using namespace AnalyzeCommand;
AnalyzeExecuteCommandInit::AnalyzeExecuteCommandInit(FacadeAnalyzeCommand& facadeAnalyzeCommand):
    AnalyzeExecuteCommand(facadeAnalyzeCommand)
{}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandInit::EndExecuteCommand(const bool wasExecute)
{
    AnalyzeExecuteCommand::EndExecuteCommand(wasExecute);
    facadeAnalyzeCommand.InitNewRepository();
}
//----------------------------------------------------------------------------------------/

