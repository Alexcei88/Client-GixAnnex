#include "parsingcommandget.h"

ParsingCommandGet::ParsingCommandGet()
{
    // регулярное выражение в случаи успешного парсинга
    QString succes = "(get)(.*)(\\(.*\\))(.*)";
    //  ресурс недоступен
    QString unsucces = "(get)(.*)(not available)";
    // причина ошибки
    QString error = "(error: )(.*)";

    // итоговый результат копирования
    // количество файлов, которые не удалось скопировать-
    QString summaryFailed = "";

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
            return;
        }

        //  в случаи успеха
        regExp.setPattern(listRegExpPossible[0]);
        if(regExp.indexIn(str) != -1)
        {
            dataAfterParsing << regExp.cap(2) << regExp.cap(4);
        }
    }
    else if(!commandStart && commandEnd)
    {
        // команда завершилась
    }
    else
    {
        // ничего не делаем
    }
}
//----------------------------------------------------------------------------------------/

