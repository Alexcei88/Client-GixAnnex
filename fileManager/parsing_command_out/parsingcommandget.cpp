#include "parsingcommandget.h"
#include "../repository/irepository.h"
#include <assert.h>

ParsingCommandGet::ParsingCommandGet(IRepository* repository) :
    IParsingCommandOut(repository)
  , startGet(false)
{
    // регулярное выражение в случаи успешного начала скачивания файла текущего файла
    QString succes1 = "(^ ?get )(.*)";
    QString succes2 = "(^ ?get )(.*)(\\(from.*)";

    // регулярное выражение в случаи успешного окончания скачивания файла(может быть как отдельной строкой идти,а может и совмещенно)
    QString succesEnd = "(.*)(ok)(.*)";

    //  ресурс недоступен
    QString unsucces = "(.*)(failed)(.*)";
    QString unsuccesAdd = "(.*)(\\d+ failed)(.*)";

    // причина ошибки
    QString error = "(error: )(.*)";
    // процесс скачивания ресурса из интернета(пока нереализованно)
    QString processDownLoad = "()";

    // итоговый результат копирования
    // количество файлов, которые не удалось скопировать-
//    QString summaryFailed = "";

    listRegExpPossible.push_back(succes1);
    listRegExpPossible.push_back(succes2);
    listRegExpPossible.push_back(unsucces);
    listRegExpPossible.push_back(unsuccesAdd);
    listRegExpPossible.push_back(error);
    listRegExpPossible.push_back(succesEnd);
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
                // в случаи неудачи начала скачивания
                regExp.setPattern(listRegExpPossible[2]);
                if(regExp.indexIn(tempStr) != -1)
                {
                    regExp.setPattern(listRegExpPossible[3]);
                    if(regExp.indexIn(tempStr) == -1)
                    {
                        startGet = false;
                        wasErrorCommand = true;
                    }
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
    dataAfterParsing << regExp.cap(1);
    emit repository->endGetContentFile(nameFileGetContent);
    wasErrorCommand = false;
}
//----------------------------------------------------------------------------------------/

