#include "iparsingcommandout.h"
#include "../shell/tshell.h"

//----------------------------------------------------------------------------------------/
IParsingCommandOut::IParsingCommandOut():
  commandStart(false)
 ,commandEnd(false)
 ,exitCodeCommand(0)
{}
//----------------------------------------------------------------------------------------/
IParsingCommandOut::~IParsingCommandOut(){};
//----------------------------------------------------------------------------------------/
void IParsingCommandOut::SetParamBeforeStartCommand()
{
    dataStdOut.clear();
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
}
//----------------------------------------------------------------------------------------/
QStringList IParsingCommandOut::GetParsingData() const
{
    return dataAfterParsing;
}
//----------------------------------------------------------------------------------------/

