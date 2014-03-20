#include "parsingerrorexecutecommandget.h"

using namespace AnalyzeCommand;

//----------------------------------------------------------------------------------------/
ParsingErrorExecuteCommandGet::ParsingErrorExecuteCommandGet(): ParsingErrorExecuteCommand()
{
    // определяем перечисление ошибок
    enum class ErrorType {
        UNKNOW_ERROR = -1,
        UNAVAIBLE_CONTENT = 0
    };    
}
//----------------------------------------------------------------------------------------/
ParsingErrorExecuteCommandGet::~ParsingErrorExecuteCommandGet()
{}
//----------------------------------------------------------------------------------------/
void ParsingErrorExecuteCommandGet::FillErrorIdDescription()
{

}
//----------------------------------------------------------------------------------------/
