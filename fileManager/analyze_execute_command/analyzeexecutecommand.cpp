#include "analyzeexecutecommand.h"
#include <assert.h>

using namespace AnalyzeCommand;

//----------------------------------------------------------------------------------------/
AnalyzeExecuteCommand::AnalyzeExecuteCommand(FacadeAnalyzeCommand &facadeAnalyzeCommand):
    facadeAnalyzeCommand(facadeAnalyzeCommand)
  , startCommand(false)
  , endCommand(false)
{
}
//----------------------------------------------------------------------------------------/
AnalyzeExecuteCommand::AnalyzeExecuteCommand(FacadeAnalyzeCommand &facadeAnalyzeCommand, const QString& pathExecuteCommand):
    facadeAnalyzeCommand(facadeAnalyzeCommand)
  , pathExecuteCommand(pathExecuteCommand)
  , startCommand(false)
  , endCommand(false)
{
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommand::StartExecuteCommand()
{
    assert(!startCommand && !endCommand);
    startCommand = true;
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommand::EndExecuteCommand(const bool wasExecute)
{
    assert(startCommand && !endCommand);
    endCommand = true;
    //wasExecute
}
//----------------------------------------------------------------------------------------/


