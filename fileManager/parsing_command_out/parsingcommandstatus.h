#ifndef PARSINGCOMMANDSTATUS_H
#define PARSINGCOMMANDSTATUS_H

#include "iparsingcommandout.h"

namespace AnalyzeCommand
{
    class AnalizeExecuteCommandStatus;
}

class ParsingCommandStatus : public IParsingCommandOut
{
public:
    ParsingCommandStatus(boost::shared_ptr<AnalyzeCommand::AnalizeExecuteCommandStatus> analyzeCommand);
    virtual void        ParsingData();

private:
    boost::shared_ptr<AnalyzeCommand::AnalizeExecuteCommandStatus> analizeCommandStatus;

};

#endif // PARSINGCOMMANDSTATUS_H
