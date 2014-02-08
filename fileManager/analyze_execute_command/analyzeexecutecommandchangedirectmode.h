#ifndef ANALYZEEXECUTECOMMANDCHANGEDIRECTMODE_H
#define ANALYZEEXECUTECOMMANDCHANGEDIRECTMODE_H

#include "analyzeexecutecommand.h"

namespace AnalyzeCommand
{
class FacadeAnalyzeCommand;

class AnalyzeExecuteCommandChangeDirectMode : public AnalyzeExecuteCommand
{
public:
    AnalyzeExecuteCommandChangeDirectMode(FacadeAnalyzeCommand& facadeAnalyzeCommand);
    virtual void        EndExecuteCommand(const bool wasExecute = true);

    void                ChangeDirectMode(const bool& mode);
    void                ErrorChangeDirectMode();

private:
    // новый режим, который был установлен командой
    bool                mode;
    bool                wasError;
};
}
#endif // ANALYZEEXECUTECOMMANDCHANGEDIRECTMODE_H
