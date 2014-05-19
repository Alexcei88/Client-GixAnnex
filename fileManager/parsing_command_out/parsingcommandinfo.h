#ifndef PARSINGCOMMANDInfo_H
#define PARSINGCOMMANDInfo_H

#include "iparsingcommandout.h"

namespace AnalyzeCommand
{
    class AnalizeExecuteCommandInfo;
}

class ParsingCommandInfo : public IParsingCommandOut
{
public:
    ParsingCommandInfo(boost::shared_ptr<AnalyzeCommand::AnalizeExecuteCommandInfo> analyzeCommand);
    virtual void        ParsingData();

private:
    boost::shared_ptr<AnalyzeCommand::AnalizeExecuteCommandInfo> analizeCommandInfo;

};

#endif // PARSINGCOMMANDInfo_H
