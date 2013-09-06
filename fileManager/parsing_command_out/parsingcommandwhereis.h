#ifndef PARSINGCOMMANDWHEREIS_H
#define PARSINGCOMMANDWHEREIS_H

#include "iparsingcommandout.h"
class ParsingCommandWhereIs : public IParsingCommandOut
{
public:
    ParsingCommandWhereIs();
    virtual void        ParsingData();
};

#endif // PARSINGCOMMANDWHEREIS_H
