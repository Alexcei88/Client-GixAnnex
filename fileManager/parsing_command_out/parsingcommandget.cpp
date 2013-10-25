#include "parsingcommandget.h"

ParsingCommandGet::ParsingCommandGet(const TShell* shell, IRepository* repository) :
    IParsingCommandOut(shell)
  , repository(repository)
  , startGet(false)
{
    // регулярное выражение в случаи успешного начала скачивания файла текущего файла
    QString succes1 = "(^ ?get)(.*)";

    // регулярное выражение в случаи успешного окончания скачивания файла(может быть как отдельной строкой идти,а может и совмещенно)
    QString succesEnd = "(.*)(ok)(.*)";

    //  ресурс недоступен
    QString unsucces = "(get)(.*)(not available)";
    // причина ошибки
    QString error = "(error: )(.*)";
    // процесс скачивания ресурса из интернета(пока нереализованно)
    QString processDownLoad = "()";

    // итоговый результат копирования
    // количество файлов, которые не удалось скопировать-
//    QString summaryFailed = "";

    listRegExpPossible.push_back(succes1);
    listRegExpPossible.push_back(unsucces);
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
        const QString str = dataStdOut.back().replace(QChar('\n'), QString(" "));

        // в случаи неудачи начала скачивания
        regExp.setPattern(listRegExpPossible[1]);
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
            StartGetContentFile();
            return;
        }

        // в случаи окончания скачивания файла
        regExp.setPattern(listRegExpPossible[3]);
        if(regExp.indexIn(str) != -1)
        {
            EndGetContentFile();

            // проверка, не началось ли новое скачивание
            const QString remainStr = regExp.cap(3);
            regExp.setPattern(listRegExpPossible[0]);
            if(regExp.indexIn(remainStr) != -1)
            {
                StartGetContentFile();
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

