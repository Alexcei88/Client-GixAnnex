#ifndef PARSINGCOMMANDGET_H
#define PARSINGCOMMANDGET_H

#include "iparsingcommandout.h"

class ParsingCommandGet : public IParsingCommandOut
{
public:
    ParsingCommandGet();
    virtual void        ParsingData();
};

#endif // PARSINGCOMMANDGET_H
