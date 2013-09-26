#ifndef PARSINGCOMMANDCLONE_H
#define PARSINGCOMMANDCLONE_H

#include "iparsingcommandout.h"

class ParsingCommandClone : public IParsingCommandOut
{
public:
    ParsingCommandClone();
    virtual void        ParsingData();
};

#endif // PARSINGCOMMANDCLONE_H
