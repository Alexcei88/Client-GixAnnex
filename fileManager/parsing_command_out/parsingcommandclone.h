#ifndef PARSINGCOMMANDCLONE_H
#define PARSINGCOMMANDCLONE_H

#include "iparsingcommandout.h"

namespace AnalyzeCommand
{
    class AnalyzeExecuteCommandClone;
}

class ParsingCommandClone : public IParsingCommandOut
{
public:
    ParsingCommandClone(boost::shared_ptr<AnalyzeCommand::AnalyzeExecuteCommandClone> analyzeCommand);
    virtual void        ParsingData();

private:
    /** @brief список регулярных выражений для парсинга данных */
    QStringList         listRegExpPossible;

    /** @brief класс парсинга*/
    QRegExp             regExp;
    // класс анализа команды clone
    boost::shared_ptr<AnalyzeCommand::AnalyzeExecuteCommandClone> analizeCommandClone;
};

#endif // PARSINGCOMMANDCLONE_H
