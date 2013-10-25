#include "parsingcommanddrop.h"

ParsingCommandDrop::ParsingCommandDrop(const TShell* shell, IRepository* repository) :
    IParsingCommandOut(shell)
  , repository(repository)
  , startDrop(false)
{
    // регулярное выражение в случаи успешного удаления
    QString succes = "(drop)(.*)(\\(.*\\))(.*)";

    // регулярное выражение в случаи успешного окончания скачивания файла(может быть как отдельной строкой идти,а может и совмещенно)
    QString succesEnd = "(.*)(ок)(.*)";

    // итоговый результат удаления
    // количество файлов, которые не удалось скопировать-
//    QString summaryFailed = "";

    listRegExpPossible.push_back(succes);
    listRegExpPossible.push_back(succesEnd);
}
//----------------------------------------------------------------------------------------/
void ParsingCommandDrop::ParsingData()
{
    // команда стартовала, но еще не завершилась
    if(commandStart && !commandEnd)
    {
        const QString str = dataStdOut.back();
        //  в случаи успеха начала скачивания
        regExp.setPattern(listRegExpPossible[0]);
        if(regExp.indexIn(str) != -1)
        {
            assert(!startDrop && "Предыдущий ресурс еще не удалился, и началось новое удаление. Что то пошло не так!!!");
            startDrop = true;
            dataAfterParsing << regExp.cap(2) << regExp.cap(4);
            wasErrorCommand = false;
            nameFileGetContent = regExp.cap(2);
            emit repository->startDropContentFile(nameFileGetContent);
            return;
        }

        // ждем окончания удаления файла
        regExp.setPattern(listRegExpPossible[1]);
        if(regExp.indexIn(str) != -1)
        {
            assert(startDrop && "Удаление ресурса не было запущено");
            startDrop = false;
            dataAfterParsing << regExp.cap(1);
            emit repository->endDropContentFile(nameFileGetContent);
            wasErrorCommand = false;
        }
        else
        {
            // остальное все нас не иттересует
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

