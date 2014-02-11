#include "parsingcommandempty.h"

//----------------------------------------------------------------------------------------/
ParsingCommandEmpty::ParsingCommandEmpty():
    IParsingCommandOut()
{}
//----------------------------------------------------------------------------------------/
ParsingCommandEmpty::ParsingCommandEmpty(boost::shared_ptr<AnalyzeCommand::AnalyzeExecuteCommand> analyzeCommand):
    IParsingCommandOut(analyzeCommand)
{}
//----------------------------------------------------------------------------------------/
void ParsingCommandEmpty::ParsingData()
{}
//----------------------------------------------------------------------------------------/
