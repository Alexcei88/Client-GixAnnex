#include "parsingcommandclone.h"
#include "../repository/irepository.h"

//----------------------------------------------------------------------------------------/
ParsingCommandClone::ParsingCommandClone(IRepository * repository):
    IParsingCommandOut(repository)
{
    // регулярное выражение в случаи успешного парсинга
    QString succes = "(Cloning into ')(.*)(')(.*)";
    //  в случаи ошибки
    QString unsucces = "(fatal: )(.*)";
    // причина ошибки
    QString error = "(error: )(.*)";

    listRegExpPossible.push_back(succes);
    listRegExpPossible.push_back(unsucces);
    listRegExpPossible.push_back(error);
}
//----------------------------------------------------------------------------------------/
void ParsingCommandClone::ParsingData()
{
    if(!commandStart && commandEnd && !dataStdOut.empty())
    {
        // выполняем парсинг
        // 1. проверка, есть ли ошибки
        regExp.setPattern(listRegExpPossible[1]);
        for(int i = 0; i < dataStdOut.size(); ++i)
        {
            const QString str = dataStdOut[i];
            if(regExp.indexIn(str) != -1)
            {
                QString errorString;
                // была ошибка, формируем сообщение об ошибке
                dataAfterParsing<<regExp.cap(1)<<regExp.cap(2);

                errorString += regExp.cap(1);
                errorString += regExp.cap(2);
                // если возможно, то пытаемся найти причину ошибки
                regExp.setPattern(listRegExpPossible[2]);
                for(int j = 0; j < dataStdOut.size(); ++j)
                {
                    const QString str = dataStdOut[j];
                    if(regExp.indexIn(str) != -1)
                    {
                        dataAfterParsing<<regExp.cap(1)<<regExp.cap(2);
                        errorString += regExp.cap(1);
                        errorString += regExp.cap(2);
                    }
                }
                emit repository->errorCloneRepository(errorString);
                wasErrorCommand = true;
                return;
            }
        }
        // если нет, то ищем директорию, куда скопировали
        const QString str = dataStdOut.at(0);
        regExp.setPattern(listRegExpPossible[0]);
        if(regExp.indexIn(str) != -1)
        {
            const QString nameFolder = regExp.cap(2);
            dataAfterParsing << nameFolder;
        }
        wasErrorCommand = false;
    }
    else
    {
        // иначе ничего не делаем
    }
}
//----------------------------------------------------------------------------------------/

