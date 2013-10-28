#include "parsingcommanddrop.h"

ParsingCommandDrop::ParsingCommandDrop(const TShell* shell, IRepository* repository) :
    IParsingCommandOut(shell)
  , repository(repository)
  , startDrop(false)
{
    // регулярные выражение в случаи успешного удаления
    QString succes1 = "(^ ?drop )(.*)";
    QString succes2 = "(^ ?drop )(.*)(\\(from.*)";

    // регулярное выражение в случаи успешного окончания скачивания файла(может быть как отдельной строкой идти,а может и совмещенно)
    QString succesEnd = "(.*)(ок)(.*)";

    // итоговый результат удаления
    // количество файлов, которые не удалось скопировать-
//    QString summaryFailed = "";

    listRegExpPossible.push_back(succes1);
    listRegExpPossible.push_back(succes2);
    listRegExpPossible.push_back(succesEnd);
}
//----------------------------------------------------------------------------------------/
void ParsingCommandDrop::ParsingData()
{
    return;
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
                //  в случаи успеха начала скачивания
                regExp.setPattern(listRegExpPossible[1]);
                if(regExp.indexIn(tempStr) != -1)
                {
                    StartDropContentFile();
                    tempStr = regExp.cap(3);
                    continue;
                }

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
