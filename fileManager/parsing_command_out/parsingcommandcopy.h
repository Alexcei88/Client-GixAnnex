#ifndef PARSINGCOMMANDCOPY_H
#define PARSINGCOMMANDCOPY_H

#include "iparsingcommandout.h"

// Qt stuff
#include <QString>

namespace AnalyzeCommand
{
    class AnalyzeExecuteCommandCopy;
}

class ParsingCommandCopy: public IParsingCommandOut
{
public:
    ParsingCommandCopy(boost::shared_ptr<AnalyzeCommand::AnalyzeExecuteCommandCopy> analyzeCommand);
    virtual void        ParsingData();

private:
    // флаг окончания скачивания ресурсов
    bool                startCopy;
    // имя текущего удаляемого ресурса
    QString             nameFileGetContent;
    //  начала копирование файла
    void                StartCopyContentFile(const QJsonDocument& doc);
    // конец копирования файла
    void                EndCopyContentFile();
    // копирование файла завершилось с ошибкой
    void                ErrorCopyContentFile(const QJsonDocument &doc);
    // класс анализа команды copy
    boost::shared_ptr<AnalyzeCommand::AnalyzeExecuteCommandCopy> analizeCommandCopy;

};

#endif // PARSINGCOMMANDCOPY_H
