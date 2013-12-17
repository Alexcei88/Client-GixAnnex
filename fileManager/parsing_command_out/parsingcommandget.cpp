#include "parsingcommandget.h"
#include "../repository/irepository.h"
#include <assert.h>

ParsingCommandGet::ParsingCommandGet(IRepository* repository) :
    IParsingCommandOut(repository)
  , startGet(false)
{
//    // регулярное выражение в случаи успешного начала скачивания файла текущего файла
    QString startGet = "(\{\"command\":\"get\")(.*)";
    QString endGet = "(\"success\":.*\})(.*)" ;
    QString JsonStr = "(\".*\":\".*\")";

    listRegExpPossible.push_back(startGet);
    listRegExpPossible.push_back(endGet);
    listRegExpPossible.push_back(JsonStr);
}
//----------------------------------------------------------------------------------------/
void ParsingCommandGet::ParsingData()
{
    // команда стартовала, но еще не завершилась
    if(commandStart && !commandEnd)
    {
        // посл полученная строка из потока вывода
        const QString str = dataStdOut.back();

        // идем построчно
        QStringList strLines = str.split("\n", QString::SkipEmptyParts);
        for(auto it = strLines.begin(); it != strLines.end(); ++it)
        {
            QString tempStr = *it;
            while(!tempStr.isEmpty())
            {
                // в случаи удачи начала скачивания
                regExp.setPattern(listRegExpPossible[0]);
                if(regExp.indexIn(tempStr) != -1)
                {
                    StartGetContentFile();
                    tempStr = "";
                    continue;
                }

                //  в случаи успеха начала скачивания
                regExp.setPattern(listRegExpPossible[1]);
                if(regExp.indexIn(tempStr) != -1)
                {
                    StartGetContentFile();
                    tempStr = regExp.cap(3);
                    continue;
                }
                regExp.setPattern(listRegExpPossible[0]);
                if(regExp.indexIn(tempStr) != -1)
                {
                    StartGetContentFile();
                    tempStr = "";
                    continue;
                }

                // в случаи окончания скачивания файла
                regExp.setPattern(listRegExpPossible[5]);
                if(regExp.indexIn(tempStr) != -1)
                {
                    EndGetContentFile();
                    tempStr = regExp.cap(3);
                    continue;
                }
                // не нашли соответствие, перрываем парсинг текущей строки
                tempStr = "";
            }
        }
    }
    else if(!commandStart && commandEnd)
    {
        // команда завершилась
    }
}
//----------------------------------------------------------------------------------------/
void ParsingCommandGet::StartGetContentFile()
{
    assert(!startGet && "Предыдущий ресурс еще не скачался, и началось новое скачивание. Что то пошло не так!!!");
    startGet = true;
    wasErrorCommand = false;

    dataAfterParsing << regExp.cap(2);
    nameFileGetContent = regExp.cap(2);
    emit repository->startGetContentFile(nameFileGetContent);
}
//----------------------------------------------------------------------------------------/
void ParsingCommandGet::EndGetContentFile()
{
    assert(startGet && "Скачивание ресурса не было запущено");
    startGet = false;
    dataAfterParsing << regExp.cap(1);
    emit repository->endGetContentFile(nameFileGetContent);
    wasErrorCommand = false;
}
//----------------------------------------------------------------------------------------/
void ParsingCommandGet::ErrorGetContentFile()
{
    assert(startGet && "Скачивание ресурса не было запущено");
    startGet = false;
    wasErrorCommand = true;
    dataAfterParsing << regExp.cap(1);
    emit repository->errorGetContentFile(nameFileGetContent, "ffff");
    wasErrorCommand = true;
}
//----------------------------------------------------------------------------------------/

