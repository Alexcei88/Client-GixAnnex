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
 ,startNewArray(false)
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

    FilterInputString(newData);
    //ParsingData();

}
//----------------------------------------------------------------------------------------/
void IParsingCommandOut::SetParamAfterEndCommand(int exitCode)
{
    commandEnd      = true;
    commandStart    = false;
    exitCodeCommand = exitCode;

    // выполняем парсинг после выполнения команды
   // ParsingData();
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
void IParsingCommandOut::ClearCurrentJSonArray()
{
    // чистим только те объекты, которые уже побывали в парсинге и являются завершенными
    for(auto it = currentJSONArray.begin(); it != currentJSONArray.end(); ++it)
    {
        currentJSONArray.erase(it);
    }
}
//----------------------------------------------------------------------------------------/
void IParsingCommandOut::FilterInputString(const QString& str)
{
    static const QString JSONStr = "(\".*\":\".*\")";
    static const QString startNewAray = "(\{\"command\":\".*\")";
    static const QString endNewAray = "(\"success\":.*\})(.*)";
    QStringList strLines = str.split("\n", QString::SkipEmptyParts);
    for(auto it = strLines.begin(); it != strLines.end(); ++it)
    {
        QString tempStr = *it;
        while(!tempStr.isEmpty())
        {
            // ищем строку, нет ли там строки начала парсинга
            // 1.
            regExp.setPattern(startNewAray);
            if(regExp.indexIn(tempStr) != -1)
            {
                assert("Констуирование старого JSON объекта еще не закончилось, а мы начинаем новое"
                       "Что то пошло не так" && !this->startNewArray);
                // мы начинаем конструирование нового объекта
                this->startNewArray = true;
                tempStr.remove(regExp.cap(1));
                break;
            }
            // 2.
            regExp.setPattern(endNewAray);
            if(regExp.indexIn(tempStr) != -1)
            {
                assert("Констуирование старого JSON объекта еще не начиналось, а мы начинаем уже заканчиваем"
                       "Что то пошло не так" && this->startNewArray);
                // мы закончили конструирование
                this->startNewArray = false;
                tempStr.remove(regExp.cap(1));
                break;
            }
            // 3.
            // 2.
            regExp.setPattern(JSONStr);
            if(regExp.indexIn(tempStr) != -1)
            {
                tempStr.remove(regExp.cap(1));
                break;
            }
            tempStr = "";
        }
    }
}
//----------------------------------------------------------------------------------------/

