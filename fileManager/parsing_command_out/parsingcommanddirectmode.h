#ifndef PARSINGCOMMANDDIRECTMODE_H
#define PARSINGCOMMANDDIRECTMODE_H

#include "iparsingcommandout.h"

class ParsingCommandDirectMode: public IParsingCommandOut
{
public:
    ParsingCommandDirectMode(IRepository* repository);
    virtual void ParsingData();
};

#endif // PARSINGCOMMANDDIRECTMODE_H
