#include "parsingcommandfind.h"
#include "../analyze_execute_command/analyzeexecutecommandfind.h"

using namespace AnalyzeCommand;
//----------------------------------------------------------------------------------------/
ParsingCommandFind::ParsingCommandFind(boost::shared_ptr<AnalyzeCommand::AnalyzeExecuteCommandFind> analyzeCommand):
    IParsingCommandOut(analyzeCommand)
  , analizeCommandFind(analyzeCommand)
{
}
//----------------------------------------------------------------------------------------/

