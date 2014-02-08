#ifndef ANALYZEEXECUTECOMMANDINIT_H
#define ANALYZEEXECUTECOMMANDINIT_H

#include "analyzeexecutecommand.h"

namespace AnalyzeCommand
{

class FacadeAnalyzeCommand;

class AnalyzeExecuteCommandInit : public AnalyzeExecuteCommand
{
public:
    AnalyzeExecuteCommandInit(FacadeAnalyzeCommand& facadeAnalyzeCommand);
    virtual void        EndExecuteCommand(const bool wasExecute = true);
};
}
#endif // ANALYZEEXECUTECOMMANDINIT_H
