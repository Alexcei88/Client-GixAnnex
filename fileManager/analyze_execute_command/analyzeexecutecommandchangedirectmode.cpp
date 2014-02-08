#include "analyzeexecutecommandchangedirectmode.h"
#include "facadeanalyzecommand.h"

using namespace AnalyzeCommand;

AnalyzeExecuteCommandChangeDirectMode::AnalyzeExecuteCommandChangeDirectMode(FacadeAnalyzeCommand& facadeAnalyzeCommand):
    AnalyzeExecuteCommand(facadeAnalyzeCommand)
  , mode(false)
  , wasError(false)
{}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandChangeDirectMode::EndExecuteCommand(const bool wasExecute)
{
    AnalyzeExecuteCommand::EndExecuteCommand(wasExecute);
    wasError ? facadeAnalyzeCommand.ErrorChangeDirectMode() : facadeAnalyzeCommand.ChangeDirectMode(mode);
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandChangeDirectMode::ChangeDirectMode(const bool& mode)
{
    this->mode = mode;
    wasError = false;
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandChangeDirectMode::ErrorChangeDirectMode()
{
    wasError = true;
}
//----------------------------------------------------------------------------------------/


