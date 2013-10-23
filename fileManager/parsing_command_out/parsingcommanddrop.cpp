#include "parsingcommanddrop.h"

ParsingCommandDrop::ParsingCommandDrop(const TShell* shell, IRepository* repository) :
    IParsingCommandOut(shell)
  , repository(repository)
  , startGet(false)
{
    // регулярное выражение в случаи успешного начала скачивания файла
    QString succes = "(get)(.*)(\\(.*\\))(.*)";

    // регулярное выражение в случаи успешного окончания скачивания файла(может быть как отдельной строкой идти,а может и совмещенно)
    QString succesEnd = "(.*)(ок)(.*)";

    //  ресурс недоступен
    QString unsucces = "(get)(.*)(not available)";
    // причина ошибки
    QString error = "(error: )(.*)";
    // процесс скачивания ресурса из интернета(пока нереализованно)
    QString processDownLoad = "()";

    // итоговый результат копирования
    // количество файлов, которые не удалось скопировать-
//    QString summaryFailed = "";

    listRegExpPossible.push_back(succes);
    listRegExpPossible.push_back(unsucces);
    listRegExpPossible.push_back(error);
    listRegExpPossible.push_back(succesEnd);
}
//----------------------------------------------------------------------------------------/
void ParsingCommandDrop::ParsingData()
{
    return;
    if(commandStart && !commandEnd)
    {
        // команда стартовала, но еще не завершилась
        // в случаи неудачи начала скачивания
        regExp.setPattern(listRegExpPossible[1]);
        const QString str = dataStdOut.back();
        if(regExp.indexIn(str) != -1)
        {
            dataAfterParsing << regExp.cap(2) << regExp.cap(3);
            wasErrorCommand = true;
            return;
        }

        //  в случаи успеха начала скачивания
        regExp.setPattern(listRegExpPossible[0]);
        if(regExp.indexIn(str) != -1)
        {
            assert(!startGet && "Предыдущий ресурс еще не скачался, и началось новое скачивание. Что то пошло не так!!!");
            startGet = true;
            dataAfterParsing << regExp.cap(2) << regExp.cap(4);
            wasErrorCommand = false;
            nameFileGetContent = regExp.cap(2);
            emit repository->startGetContentFile(nameFileGetContent);
            return;
        }

        regExp.setPattern(listRegExpPossible[3]);
        if(regExp.indexIn(str) != -1)
        {
            assert(startGet && "Скачивание ресурса не было запущено");
            startGet = false;
            dataAfterParsing << regExp.cap(1);
            emit repository->endGetContentFile(nameFileGetContent);
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

