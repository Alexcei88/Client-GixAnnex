#ifndef PARSINGCLONEEMPTY_H
#define PARSINGCLONEEMPTY_H

#include "iparsingcommandout.h"
class ParsingCommandEmpty: public IParsingCommandOut
{
public:
    ParsingCommandEmpty();
    ParsingCommandEmpty(boost::shared_ptr<AnalyzeCommand::AnalyzeExecuteCommand> analyzeCommand);
    virtual void        ParsingData();
};

#endif // PARSINGCLONEEMPTY_H
