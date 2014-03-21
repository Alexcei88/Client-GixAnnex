#ifndef PARSINGERROREXECUTECOMMANDGET_H
#define PARSINGERROREXECUTECOMMANDGET_H

#include "parsingerrorexecutecommandwithfiles.h"

namespace AnalyzeCommand
{
class ParsingErrorExecuteCommandGet : public ParsingErrorExecuteCommandWithFiles
{
public:
    ParsingErrorExecuteCommandGet();
    ~ParsingErrorExecuteCommandGet();

private:
    virtual void        FillErrorIdDescription();

};
}

#endif // PARSINGERROREXECUTECOMMANDGET_H
