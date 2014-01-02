#ifndef PARSINGCOMMANDFIND_H
#define PARSINGCOMMANDFIND_H

#include "iparsingcommandout.h"

namespace AnalyzeCommand
{
    class AnalyzeExecuteCommandFind;
}

class ParsingCommandFind : public IParsingCommandOut
{
public:
    ParsingCommandFind(boost::shared_ptr<AnalyzeCommand::AnalyzeExecuteCommandFind> analyzeCommand);

private:
    boost::shared_ptr<AnalyzeCommand::AnalyzeExecuteCommandFind> analizeCommandFind;

};

#endif // PARSINGCOMMANDFIND_H
