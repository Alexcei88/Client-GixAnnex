#include "parsingcommandwhereis.h"

//----------------------------------------------------------------------------------------/
ParsingCommandWhereIs::ParsingCommandWhereIs(const TShell* shell): IParsingCommandOut(shell)
{
    // регулярное выражение в случаи успешного парсинга
    QString succes = "(whereis)(.*)(\()(\\d)";
    //  ресурс недоступен
    QString unsucces = "(get)(.*)(not available)";
    // причина ошибки
    QString error = "(error: )(.*)";

    listRegExpPossible.push_back(succes);
    listRegExpPossible.push_back(unsucces);
    listRegExpPossible.push_back(error);
    regExp.setPattern("(Cloning into ')(.*)(')(.*)");
}
//----------------------------------------------------------------------------------------/
void ParsingCommandWhereIs::ParsingData()
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
        // команда завершилась, ничего не делаем
    }
    else
    {
        // ничего не делаем
    }
}
//----------------------------------------------------------------------------------------/
