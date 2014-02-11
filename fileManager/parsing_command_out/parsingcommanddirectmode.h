#ifndef PARSINGCOMMANDDIRECTMODE_H
#define PARSINGCOMMANDDIRECTMODE_H

#include "iparsingcommandout.h"

namespace AnalyzeCommand
{
    class AnalyzeExecuteCommandChangeDirectMode;
}

class ParsingCommandDirectMode: public IParsingCommandOut
{
public:
    ParsingCommandDirectMode(boost::shared_ptr<AnalyzeCommand::AnalyzeExecuteCommandChangeDirectMode> analyzeCommand);
    virtual void ParsingData();

private:
    // класс анализа команды drop
    boost::shared_ptr<AnalyzeCommand::AnalyzeExecuteCommandChangeDirectMode> analizeCommandChangeMode;

};

#endif // PARSINGCOMMANDDIRECTMODE_H
