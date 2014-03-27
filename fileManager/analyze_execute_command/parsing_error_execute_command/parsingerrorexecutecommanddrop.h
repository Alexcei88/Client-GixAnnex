#ifndef PARSINGERROREXECUTECOMMANDDROP_H
#define PARSINGERROREXECUTECOMMANDDROP_H

#include "parsingerrorexecutecommandwithfiles.h"

namespace AnalyzeCommand
{
class ParsingErrorExecuteCommandDrop : public ParsingErrorExecuteCommandWithFiles
{
public:
    ParsingErrorExecuteCommandDrop();

private:
    virtual void        FillErrorIdDescription();


};

}
#endif // PARSINGERROREXECUTECOMMANDDROP_H
