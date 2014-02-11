#ifndef PARSINGCOMMANDDROP_H
#define PARSINGCOMMANDDROP_H

#include "iparsingcommandout.h"

// Qt stuff
#include <QString>

namespace AnalyzeCommand
{
    class AnalyzeExecuteCommandDrop;
}

class ParsingCommandDrop : public IParsingCommandOut
{
public:
    ParsingCommandDrop(boost::shared_ptr<AnalyzeCommand::AnalyzeExecuteCommandDrop> analyzeCommand);
    virtual void        ParsingData();

private:
    // флаг окончания скачивания ресурсов
    bool                startDrop;
    // имя текущего удаляемого ресурса
    QString             nameFileGetContent;
    //  начала удаления файла
    void                StartDropContentFile(const QJsonDocument& doc);
    // конец удаления файла
    void                EndDropContentFile();
    // удаление файла завершилось с ошибкой
    void                ErrorDropContentFile(const QJsonDocument &doc);
    // класс анализа команды drop
    boost::shared_ptr<AnalyzeCommand::AnalyzeExecuteCommandDrop> analizeCommandDrop;

};

#endif // PARSINGCOMMANDDROP_H
