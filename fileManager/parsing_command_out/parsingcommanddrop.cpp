#include "parsingcommanddrop.h"
#include <assert.h>
#include "../repository/irepository.h"

ParsingCommandDrop::ParsingCommandDrop(IRepository* repository) :
    IParsingCommandOut(repository)
  , startDrop(false)
{
    // регулярные выражение в случаи успешного удаления
    QString succes1 = "(^ ?drop )(.*)";
    QString succes2 = "(^ ?drop )(.*)(\\s+ok)";

    // регулярное выражение в случаи успешного окончания скачивания файла(может быть как отдельной строкой идти,а может и совмещенно)
    QString succesEnd = "(.*)(ok)(.*)";

    // в случаи неудачной попытки удаление контента(например, количество коий меньше 0)
    QString unsucces = "(.*)(failed)(.*)";
    QString unsuccesAdd = "(.*)(\\d+ failed)(.*)";

    // итоговый результат удаления
    // количество файлов, которые не удалось скопировать-
//    QString summaryFailed = "";

    listRegExpPossible.push_back(succes1);
    listRegExpPossible.push_back(succes2);
    listRegExpPossible.push_back(succesEnd);
    listRegExpPossible.push_back(unsucces);
    listRegExpPossible.push_back(unsuccesAdd);
}
//----------------------------------------------------------------------------------------/
void ParsingCommandDrop::ParsingData()
{
    // команда стартовала, но еще не завершилась
    if(commandStart && !commandEnd)
    {
        const QString str = dataStdOut.back();

        // идем построчно
        QStringList strLines = str.split("\n", QString::SkipEmptyParts);
        for(auto it = strLines.begin(); it != strLines.end(); ++it)
        {
            QString tempStr = *it;
            while(!tempStr.isEmpty())
            {
                //  случаи неудачного окончания скачивания файла
                regExp.setPattern(listRegExpPossible[3]);
                if(regExp.indexIn(tempStr) != -1)
                {
                    regExp.setPattern(listRegExpPossible[4]);
                    if(regExp.indexIn(tempStr) == -1)
                    {
                        ErrorDropContentFile();
                    }
                    tempStr = "";
                    continue;
                }
                // в случаи успеха начала скачивания и немедленного завершения скачивания
                regExp.setPattern(listRegExpPossible[1]);
                if(regExp.indexIn(tempStr) != -1)
                {
                    StartDropContentFile();
                    EndDropContentFile();
                    tempStr = "";
                    continue;
                }

                //  в случаи успеха начала скачивания
                regExp.setPattern(listRegExpPossible[0]);
                if(regExp.indexIn(tempStr) != -1)
                {
                    StartDropContentFile();
                    tempStr = "";
                    continue;
                }

                // ждем окончания удаления файла
                regExp.setPattern(listRegExpPossible[2]);
                if(regExp.indexIn(tempStr) != -1)
                {
                    EndDropContentFile();
                    tempStr = regExp.cap(3);
                    continue;
                }
                tempStr = "";
            }
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
void ParsingCommandDrop::StartDropContentFile()
{
    assert(!startDrop && "Предыдущий ресурс еще не удалился, и началось новое удаление. Что то пошло не так!!!");
    startDrop = true;
    dataAfterParsing << regExp.cap(2) << regExp.cap(4);
    wasErrorCommand = false;
    nameFileGetContent = regExp.cap(2);
    emit repository->startDropContentFile(nameFileGetContent);
}
//----------------------------------------------------------------------------------------/
void ParsingCommandDrop::EndDropContentFile()
{
    assert(startDrop && "Удаление ресурса не было запущено");
    startDrop = false;
    dataAfterParsing << regExp.cap(1);
    wasErrorCommand = false;
    emit repository->endDropContentFile(nameFileGetContent);
}
//----------------------------------------------------------------------------------------/
void ParsingCommandDrop::ErrorDropContentFile()
{
    assert(startDrop && "Удаление ресурса не было запущено");
    startDrop = false;
    dataAfterParsing << regExp.cap(1);
    wasErrorCommand = false;
    emit repository->errorDropContentFile(nameFileGetContent, "Error");
}
//----------------------------------------------------------------------------------------/
