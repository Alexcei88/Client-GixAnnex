#ifndef PARSINGCOMMANDWHEREIS_H
#define PARSINGCOMMANDWHEREIS_H

#include "iparsingcommandout.h"
class ParsingCommandWhereIs : public IParsingCommandOut
{
public:
    ParsingCommandWhereIs(const TShell *shell);
    virtual void        ParsingData();
};

#endif // PARSINGCOMMANDWHEREIS_H
