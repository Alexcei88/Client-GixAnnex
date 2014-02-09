#include "analyzeexecutecommandchangedirectmode.h"
#include "facadeanalyzecommand.h"

using namespace AnalyzeCommand;

AnalyzeExecuteCommandChangeDirectMode::AnalyzeExecuteCommandChangeDirectMode(FacadeAnalyzeCommand& facadeAnalyzeCommand):
    AnalyzeExecuteCommand(facadeAnalyzeCommand)
  , mode(false)
  , wasError(false)
  , wasTryChangeMode(false)
{}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandChangeDirectMode::EndExecuteCommand(const bool wasExecute)
{
    AnalyzeExecuteCommand::EndExecuteCommand(wasExecute);
    if(wasTryChangeMode)
        wasError ? facadeAnalyzeCommand.ErrorChangeDirectMode() : facadeAnalyzeCommand.ChangeDirectMode(mode);
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandChangeDirectMode::ChangeDirectMode(const bool& mode)
{
    this->mode = mode;
    wasError = false;
    wasTryChangeMode = true;
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandChangeDirectMode::ErrorChangeDirectMode()
{
    wasError = true;
    wasTryChangeMode = true;
}
//----------------------------------------------------------------------------------------/
void AnalyzeExecuteCommandChangeDirectMode::UnChangeDirectMode()
{
    wasTryChangeMode = false;
}
//----------------------------------------------------------------------------------------/



