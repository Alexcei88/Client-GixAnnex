#ifndef ANALYZEEXECUTECOMMANDFIND_H
#define ANALYZEEXECUTECOMMANDFIND_H

#include "analyzeexecutecommand.h"

namespace AnalyzeCommand
{

class FacadeAnalyzeCommand;

class AnalyzeExecuteCommandFind: public AnalyzeExecuteCommand
{
public:
    AnalyzeExecuteCommandFind(FacadeAnalyzeCommand& facadeAnalyzeCommand);
};
}

#endif // ANALYZEEXECUTECOMMANDFIND_H
