#include "parsingcommandwhereis.h"

//----------------------------------------------------------------------------------------/
ParsingCommandWhereIs::ParsingCommandWhereIs(): IParsingCommandOut()
{}
//----------------------------------------------------------------------------------------/
void ParsingCommandWhereIs::ParsingData()
{
    return;

#if 0
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
#endif
}
//----------------------------------------------------------------------------------------/
