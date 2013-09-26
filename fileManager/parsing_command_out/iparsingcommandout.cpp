#include "iparsingcommandout.h"
#include "../shell/tshell.h"

using namespace GANN_DEFINE;

//----------------------------------------------------------------------------------------/
IParsingCommandOut::IParsingCommandOut():
  commandStart(false)
 ,commandEnd(false)
 ,exitCodeCommand(0)
 ,wasErrorCommand(false)
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
    QString newData(TShell::GetInstance()->readStandartOutput());

    dataStdOut << newData;
    std::cout<<"1. "<<newData.toStdString()<<std::endl;

    ParsingData();

    emit readyNewDataStdOut();
}
//----------------------------------------------------------------------------------------/
void IParsingCommandOut::SetParamAfterEndCommand(int exitCode)
{
    commandEnd      = true;
    commandStart    = false;
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
    if(commandEnd == true && commandStart == false)
    {
        if(wasErrorCommand || exitCodeCommand)
            return ERROR_EXECUTE;
        else
            return NO_ERROR;
    }
    else
        return NO_ERROR;
}

