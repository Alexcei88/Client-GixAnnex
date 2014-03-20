#ifndef PARSINGERROREXECUTECOMMANDDROP_H
#define PARSINGERROREXECUTECOMMANDDROP_H

#include "parsingerrorexecutecommand.h"

namespace AnalyzeCommand
{
class ParsingErrorExecuteCommandDrop : public ParsingErrorExecuteCommand
{
public:
    ParsingErrorExecuteCommandDrop();

private:
    virtual void        FillErrorIdDescription();


};

}
#endif // PARSINGERROREXECUTECOMMANDDROP_H
