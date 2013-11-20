#include "iparsingcommandout.h"
#include "../shell/tshell.h"
#include "../repository/irepository.h"

using namespace GANN_DEFINE;

//----------------------------------------------------------------------------------------/
IParsingCommandOut::IParsingCommandOut(IRepository *repository):
  commandStart(false)
 ,commandEnd(false)
 ,exitCodeCommand(0)
 ,wasErrorCommand(false)
 ,repository(repository)
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
    exitCodeCommand = -2;
}
//----------------------------------------------------------------------------------------/
void IParsingCommandOut::SetNewDataStdOut()
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
void IParsingCommandOut::SetShell(TShell* shell)
{
    this->shell = shell;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS IParsingCommandOut::GetCodeError() const
{
    if(commandEnd == true && exitCodeCommand != -2)
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

