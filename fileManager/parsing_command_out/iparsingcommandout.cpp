#include "iparsingcommandout.h"
#include "../shell/tshell.h"

using namespace GANN_DEFINE;

//----------------------------------------------------------------------------------------/
IParsingCommandOut::IParsingCommandOut(const TShell *shell):
  commandStart(false)
 ,commandEnd(false)
 ,exitCodeCommand(0)
 ,wasErrorCommand(false)
 ,shell(shell)
{}
//----------------------------------------------------------------------------------------/
IParsingCommandOut::~IParsingCommandOut(){};
//----------------------------------------------------------------------------------------/
void IParsingCommandOut::SetParamBeforeStartCommand()
{
    dataStdOut.clear();
    dataAfterParsing.clear();
    commandStart    = true;
    commandEnd      = false;
}
//----------------------------------------------------------------------------------------/
void IParsingCommandOut::GetNewDataStdOut()
{
    QString newData(shell->readStandartOutput());

    dataStdOut << newData;
    std::cout<<"1. "<<newData.toStdString()<<std::endl;

    ParsingData();

    emit readyNewDataStdOut();
}
//----------------------------------------------------------------------------------------/
void IParsingCommandOut::SetParamAfterEndCommand(int exitCode)
{
    commandEnd      = true;
    commandStart    = true;
    exitCodeCommand = exitCode;

    // выполняем парсинг после выполнения команды
    ParsingData();
}
//----------------------------------------------------------------------------------------/
QStringList IParsingCommandOut::GetParsingData() const
{
    return dataAfterParsing;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS IParsingCommandOut::GetCodeError() const
{
    if(commandEnd == true && commandStart == true)
    {
        // команда была запущена и выполнена до конца
        if(wasErrorCommand || exitCodeCommand)
            return ERROR_EXECUTE;
        else
            return NO_ERROR;
    }
    else
    {
        if(!commandStart)
            return ERROR_NO_STARTED;
        else if(!commandEnd)
            return ERROR_NO_FINISHED;
        return NO_ERROR;
    }
}
//----------------------------------------------------------------------------------------/

