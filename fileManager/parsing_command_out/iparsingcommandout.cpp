#include "iparsingcommandout.h"
#include "../shell/tshell.h"
#include "../analyze_execute_command/analyzeexecutecommand.h"

// Qt stuff
#include <QJsonObject>

using namespace GANN_DEFINE;
using namespace AnalyzeCommand;

//----------------------------------------------------------------------------------------/
IParsingCommandOut::IParsingCommandOut():
   commandStart(false)
 , commandEnd(false)
 , exitCodeCommand(0)
 , wasErrorCommand(false)
 , keyStartDoc("command")
 , keyEndDoc("success")
 , startNewDocument(false)
{}
//----------------------------------------------------------------------------------------/
IParsingCommandOut::IParsingCommandOut(boost::shared_ptr<AnalyzeExecuteCommand> analyzeCommand):
   commandStart(false)
 , commandEnd(false)
 , exitCodeCommand(0)
 , wasErrorCommand(false)
 , analyzeCommand(analyzeCommand)
 , keyStartDoc("command")
 , keyEndDoc("success")
 , startNewDocument(false)
{}
//----------------------------------------------------------------------------------------/
IParsingCommandOut::~IParsingCommandOut(){};
//----------------------------------------------------------------------------------------/
void IParsingCommandOut::SetParamBeforeStartCommand()
{
    dataStdOut.clear();
    commandStart    = true;
    commandEnd      = false;
    exitCodeCommand = -2;

    if(analyzeCommand.get())
        analyzeCommand->StartExecuteCommand();
}
//----------------------------------------------------------------------------------------/
void IParsingCommandOut::SetParamAfterEndCommand(int exitCode)
{
    commandEnd      = true;
    commandStart    = false;
    exitCodeCommand = exitCode;

    // выполняем парсинг после выполнения команды
    ParsingData();

    if(analyzeCommand.get())
        analyzeCommand->EndExecuteCommand();
}
//----------------------------------------------------------------------------------------/
void IParsingCommandOut::SetParamErrorExecuteCommand(QProcess::ProcessError& error)
{
}
//----------------------------------------------------------------------------------------/
void IParsingCommandOut::SetNewDataStdOut()
{
    QString newData(shell->readStandartOutput());

    dataStdOut << newData;
    std::cout<<"1. "<<newData.toStdString()<<std::endl;

    FilterInputString(newData);
    ParsingData();
    // сохраняем последний документ
    if(!arrayJSONDocument.empty())
        lastJSONDocument = arrayJSONDocument.back();
    // чистим вектор документов
    arrayJSONDocument.clear();
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
bool IParsingCommandOut::IsEndMiniCommand(const QJsonDocument& doc, bool& ok) const
{
    assert(doc.isObject());
    QJsonObject object = doc.object();
    if(object.find(keyEndDoc) != object.end())
    {
        ok = object.take(keyEndDoc).toBool();
        return true;
    }
    ok = false;
    return false;

}
//----------------------------------------------------------------------------------------/
void IParsingCommandOut::FilterInputString(const QString& str)
{
    std::vector<QJsonDocument> parseNewDocument;
    QJsonDocument lastDoc;
    // идем построчно
    QStringList strLines = str.split("\n", QString::SkipEmptyParts);
    for(auto it = strLines.begin(); it != strLines.end(); ++it)
    {
        QString tempStr = *it;
        while(!tempStr.isEmpty())
        {
            if(!startNewDocument)
            {
                assert("Накапливаемая JSON строка должна быть пустой. Что то пошло не так" && strJSONData.isEmpty());
                // документ еще не создан, поэтому создаем его заново, во входной строке должен быть параметр command
                QJsonParseError error;
                QJsonDocument doc = QJsonDocument::fromJson(tempStr.toUtf8(), &error);
                if(doc.isNull())
                {
                    QString strNoError = ProcessingErrorString(tempStr, &error);
                    if(!strNoError.isEmpty())
                    {
                        doc = QJsonDocument::fromJson(strNoError.toUtf8(), &error);
                        assert(!doc.isNull());
                        assert(doc.isObject());
                        if(doc.isObject())
                        {
                            QJsonObject object = doc.object();
                            assert(object.find(keyStartDoc) != object.end());
                            startNewDocument = true;

                            // сохраняем временный документ
                            lastDoc = doc;
                        }
                    }
                }
                else
                {
                    // документ уже создаем готовый
                    // в этом документе должны быть параметры command и success
                    assert(doc.isObject());
                    if(doc.isObject())
                    {
                        QJsonObject object = doc.object();
                        assert(object.find(keyStartDoc) != object.end());
                        assert(object.find(keyEndDoc) != object.end());

                        // сохранили этот документ
                        parseNewDocument.push_back(doc);
                    }
                }
            }
            else
            {
                assert("Накапливаемая JSON строка не должна быть пустой. Что то пошло не так" && !strJSONData.isEmpty());
                // документ уже создан
                QJsonParseError error;
                const QString commonStr = strJSONData + tempStr;
                QJsonDocument doc = QJsonDocument::fromJson(commonStr.toUtf8(), &error);
                if(doc.isNull())
                {
                    QString strNoError = ProcessingErrorString(commonStr, &error);
                    if(!strNoError.isEmpty())
                    {
                        doc = QJsonDocument::fromJson(strNoError.toUtf8(), &error);
                        assert(!doc.isNull());
                        assert(doc.isObject());
                        if(doc.isObject())
                        {
                            QJsonObject object = doc.object();
                            assert(object.find(keyEndDoc) == object.end());
                            // сохраняем временный документ
                            lastDoc = doc;
                        }
                    }
                }
                else
                {
                    // в этом документе должны быть параметры success
                    assert(doc.isObject());
                    if(doc.isObject())
                    {
                        QJsonObject object = doc.object();
                        assert(object.find(keyStartDoc) != object.end());
                        assert(object.find(keyEndDoc) != object.end());

                        // сохраняем этот документ
                        parseNewDocument.push_back(doc);

                        // сбрасываем последний хранившийся документ
                        lastDoc = QJsonDocument::fromJson("ffgg");
                        // сбрасываем флаг начала получения нового документа
                        startNewDocument = false;

                        strJSONData = "";
                    }
                }
            }
            tempStr = "";
        }
    }

    arrayJSONDocument.assign(parseNewDocument.begin(), parseNewDocument.end());
    if(!lastDoc.isNull())
        arrayJSONDocument.push_back(lastDoc);
}
//----------------------------------------------------------------------------------------/
QString IParsingCommandOut::ProcessingErrorString(const QString& str, const QJsonParseError* parseError)
{
    QString retStr = str;
    int offset = parseError->offset;
    QString tempStr = retStr;

    switch(parseError->error)
    {
        case QJsonParseError::UnterminatedObject: // не хватает в конце закрывающей круглой скобки
            // у нас здесь два варианта, либо offset без смещения, либо со смещением влево, так работает Qt класс
            tempStr.remove(offset, str.length() - offset);
            if(!QJsonDocument::fromJson((tempStr + "}").toUtf8()).isNull())
            {
               retStr = tempStr;
            }
            else
            {
                --offset;
                retStr.remove(offset, str.length() - offset);
            }

            strJSONData = retStr;
            retStr += "}";
            break;

        case QJsonParseError::UnterminatedString: // не хватает в конце закрывающей круглой скобки
            retStr.remove(offset, str.length() - offset);
            strJSONData = retStr;
            retStr += "}";break;

        case QJsonParseError::UnterminatedArray: // не хватает в конце закрывающей квадратной скобки
            retStr.remove(offset, str.length() - offset);
            strJSONData = retStr;
            retStr += "]"; break;
        case QJsonParseError::IllegalValue: // неверное значение, поэтому приравниваем пустую строку
            // strJSONData не трогаем
            retStr = ""; break;

        default:
            assert("При парсинге JSON-строки произошла неизвестная ошибка." && false);
    }
    return retStr;
}
//----------------------------------------------------------------------------------------/
