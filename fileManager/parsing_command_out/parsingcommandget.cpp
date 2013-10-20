#include "parsingcommandget.h"

ParsingCommandGet::ParsingCommandGet(const TShell* shell, const IRepository* repository) : IParsingCommandOut(shell)
{
    // регулярное выражение в случаи успешного парсинга
    QString succes = "(get)(.*)(\\(.*\\))(.*)";
    //  ресурс недоступен
    QString unsucces = "(get)(.*)(not available)";
    // причина ошибки
    QString error = "(error: )(.*)";
    // процесс скачивания ресурса из интернета
    QString processDownLoad = "()";


    // итоговый результат копирования
    // количество файлов, которые не удалось скопировать-
//    QString summaryFailed = "";

    listRegExpPossible.push_back(succes);
    listRegExpPossible.push_back(unsucces);
    listRegExpPossible.push_back(error);
    regExp.setPattern("(Cloning into ')(.*)(')(.*)");
}
//----------------------------------------------------------------------------------------/
void ParsingCommandGet::ParsingData()
{
    if(commandStart && !commandEnd)
    {
        // команда стартовала, но еще не завершилась
        // в случаи неудачи
        regExp.setPattern(listRegExpPossible[1]);
        const QString str = dataStdOut.back();
        if(regExp.indexIn(str) != -1)
        {
            dataAfterParsing << regExp.cap(2) << regExp.cap(3);
            wasErrorCommand = true;
            return;
        }

        //  в случаи успеха
        regExp.setPattern(listRegExpPossible[0]);
        if(regExp.indexIn(str) != -1)
        {
            dataAfterParsing << regExp.cap(2) << regExp.cap(4);
            wasErrorCommand = false;
        }
        else
        {
            // неизвестная ошибка, которая непропарсилась
            wasErrorCommand = true;
        }

    }
    else if(!commandStart && commandEnd)
    {
//        wasErrorCommand = false;
        // команда завершилась
    }
    else
    {
        // ничего не делаем
    }
}
//----------------------------------------------------------------------------------------/

