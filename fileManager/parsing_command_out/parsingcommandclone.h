#ifndef PARSINGCOMMANDCLONE_H
#define PARSINGCOMMANDCLONE_H

#include "iparsingcommandout.h"

class ParsingCommandClone : public IParsingCommandOut
{
public:
    ParsingCommandClone(IRepository* repository);
    virtual void        ParsingData();
};

#endif // PARSINGCOMMANDCLONE_H
