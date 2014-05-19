#include "parsingerrorexecutecommanddrop.h"

using namespace AnalyzeCommand;

//----------------------------------------------------------------------------------------/
ParsingErrorExecuteCommandDrop::ParsingErrorExecuteCommandDrop():
    ParsingErrorExecuteCommandWithFiles()
{
    FillErrorIdDescription();
}
//----------------------------------------------------------------------------------------/
void ParsingErrorExecuteCommandDrop::FillErrorIdDescription()
{   
    errorIdDescription[ErrorType::DROP_HAVE_CONTENT_COUNT_MINIMUM] = "Gjrgh";
}
//----------------------------------------------------------------------------------------/
