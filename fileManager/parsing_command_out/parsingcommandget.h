#ifndef PARSINGCOMMANDGET_H
#define PARSINGCOMMANDGET_H

#include "iparsingcommandout.h"

class ParsingCommandGet : public IParsingCommandOut
{
public:
    ParsingCommandGet(const TShell *shell);
    virtual void        ParsingData();
};

#endif // PARSINGCOMMANDGET_H
