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
void AnalyzeExecuteCommand::StartExecuteCommand()
{
    assert(!startCommand && !endCommand);
    startCommand = true;
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommand::EndExecuteCommand()
{
    assert(startCommand && !endCommand);
    endCommand = true;
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommand::SetPathExecuteCommand(const QString& path)
{
    pathExecuteCommand = path;
}
//----------------------------------------------------------------------------------------/


