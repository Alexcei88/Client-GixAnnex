#ifndef PARSINGCOMMANDCLONE_H
#define PARSINGCOMMANDCLONE_H

#include "iparsingcommandout.h"

namespace AnalyzeCommand
{
    class AnalyzeExecuteCommand;
}

class ParsingCommandClone : public IParsingCommandOut
{
public:
    ParsingCommandClone(boost::shared_ptr<AnalyzeCommand::AnalyzeExecuteCommand> analyzeCommand);
    virtual void        ParsingData();

private:
    /** @brief список регулярных выражений для парсинга данных */
    QStringList         listRegExpPossible;

    /** @brief класс парсинга*/
    QRegExp             regExp;
};

#endif // PARSINGCOMMANDCLONE_H
