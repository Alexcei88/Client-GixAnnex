#include "parsingerrorexecutecommand.h"
#include "analyze_execute_command/analizediraction.h"

// std stuff
#include <algorithm>

using namespace AnalyzeCommand;

//----------------------------------------------------------------------------------------/
ParsingErrorExecuteCommand::ParsingErrorExecuteCommand()
{}
//----------------------------------------------------------------------------------------/
ParsingErrorExecuteCommand::~ParsingErrorExecuteCommand()
{}
//----------------------------------------------------------------------------------------/
ParsingErrorExecuteCommand::ErrorType ParsingErrorExecuteCommand::GetIdError(const QString& error) const
{
    if(auto it = std::find(errorIdDescription.begin(), errorIdDescription.end(), error) != errorIdDescription.end())
    {
        const QString string_(it);
        // мы нашли ошибку среди зарегестрированных
        return errorIdDescription.key(string_);
    }
    else {
        return static_cast<ErrorType>(-1);
    }
}
//----------------------------------------------------------------------------------------/

