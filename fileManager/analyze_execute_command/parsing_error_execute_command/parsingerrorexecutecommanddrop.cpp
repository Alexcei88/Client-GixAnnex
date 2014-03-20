#include "parsingerrorexecutecommanddrop.h"

using namespace AnalyzeCommand;

//----------------------------------------------------------------------------------------/
ParsingErrorExecuteCommandDrop::ParsingErrorExecuteCommandDrop(): ParsingErrorExecuteCommand()
{
    // определяем перечисление ошибок
    enum class ErrorType {
        UNKNOW_ERROR = -1,
        HAVE_CONTENT_COUNT_MINIMUM = 0
    };
}
//----------------------------------------------------------------------------------------/
void ParsingErrorExecuteCommandDrop::FillErrorIdDescription()
{

}
//----------------------------------------------------------------------------------------/
