#ifndef PARSINGCLONEEMPTY_H
#define PARSINGCLONEEMPTY_H

#include "iparsingcommandout.h"
class ParsingCommandEmpty: public IParsingCommandOut
{
public:
    ParsingCommandEmpty(const TShell* shell);
    virtual void        ParsingData();
};

#endif // PARSINGCLONEEMPTY_H
