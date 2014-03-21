#include "parsingerrorexecutecommandget.h"

using namespace AnalyzeCommand;

//----------------------------------------------------------------------------------------/
ParsingErrorExecuteCommandGet::ParsingErrorExecuteCommandGet():
    ParsingErrorExecuteCommandWithFiles()
{
    FillErrorIdDescription();
}
//----------------------------------------------------------------------------------------/
ParsingErrorExecuteCommandGet::~ParsingErrorExecuteCommandGet()
{}
//----------------------------------------------------------------------------------------/
void ParsingErrorExecuteCommandGet::FillErrorIdDescription()
{   
    errorIdDescription[ErrorType::GET_UNAVAIBLE_CONTENT] = "not avaible";
}
//----------------------------------------------------------------------------------------/
