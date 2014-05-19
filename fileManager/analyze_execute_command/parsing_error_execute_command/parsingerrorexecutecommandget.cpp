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
    // ресурс недоступен
    errorIdDescription[ErrorType::GET_UNAVAIBLE_CONTENT] = "not available";

    auto callbackSolution = [&](const QString& file)->void {
        std::cout<<"1"<<std::endl;

    };
    funcErrorSolution[ErrorType::GET_UNAVAIBLE_CONTENT] = callbackSolution;

    ErrorDescriptionView desciptionView;
    errorDescriptionView[ErrorType::GET_UNAVAIBLE_CONTENT] = desciptionView;
}
//----------------------------------------------------------------------------------------/
