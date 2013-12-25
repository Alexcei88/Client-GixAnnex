#ifndef PARSINGCOMMANDDIRECTMODE_H
#define PARSINGCOMMANDDIRECTMODE_H

#include "iparsingcommandout.h"

class ParsingCommandDirectMode: public IParsingCommandOut
{
public:
    ParsingCommandDirectMode(boost::shared_ptr<AnalyzeCommand::AnalyzeExecuteCommand> analyzeCommand);
    virtual void ParsingData();
};

#endif // PARSINGCOMMANDDIRECTMODE_H
