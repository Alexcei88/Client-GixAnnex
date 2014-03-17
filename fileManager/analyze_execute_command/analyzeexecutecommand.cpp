#include "analyzeexecutecommand.h"
#include <assert.h>
#include "facadeanalyzecommand.h"

using namespace AnalyzeCommand;

//----------------------------------------------------------------------------------------/
AnalyzeExecuteCommand::AnalyzeExecuteCommand(FacadeAnalyzeCommand &facadeAnalyzeCommand):
    facadeAnalyzeCommand(facadeAnalyzeCommand)
  , atomicFlagExecuteCommand(facadeAnalyzeCommand.atomicFlagExecuteCommand.get())
  , startCommand(false)
  , endCommand(false)
{}
//----------------------------------------------------------------------------------------/
AnalyzeExecuteCommand::AnalyzeExecuteCommand(FacadeAnalyzeCommand &facadeAnalyzeCommand, const QString& pathExecuteCommand):
    facadeAnalyzeCommand(facadeAnalyzeCommand)
  , pathExecuteCommand(pathExecuteCommand)
  , startCommand(false)
  , endCommand(false)
{}
//----------------------------------------------------------------------------------------/
AnalyzeExecuteCommand::~AnalyzeExecuteCommand()
{}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommand::StartExecuteCommand()
{
    assert(!startCommand && !endCommand);
    startCommand = true;
    facadeAnalyzeCommand.SetCurrentExecuteCommand(this);
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommand::EndExecuteCommand(const bool wasExecute)
{
    // проверяем на assert только в том случаи, если команда стартонула
    if(wasExecute)
        assert(startCommand && !endCommand);
    endCommand = true;
    facadeAnalyzeCommand.ResetCurrentExecuteCommand();
}
//----------------------------------------------------------------------------------------/


