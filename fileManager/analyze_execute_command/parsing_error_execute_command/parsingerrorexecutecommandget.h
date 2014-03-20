#ifndef PARSINGERROREXECUTECOMMANDGET_H
#define PARSINGERROREXECUTECOMMANDGET_H

#include "parsingerrorexecutecommand.h"

namespace AnalyzeCommand
{
class ParsingErrorExecuteCommandGet : public ParsingErrorExecuteCommand
{
public:
    ParsingErrorExecuteCommandGet();
    ~ParsingErrorExecuteCommandGet();

private:
    virtual void        FillErrorIdDescription();

};
}

#endif // PARSINGERROREXECUTECOMMANDGET_H
