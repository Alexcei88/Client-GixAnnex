#ifndef PARSINGCOMMANDGET_H
#define PARSINGCOMMANDGET_H

#include "iparsingcommandout.h"
#include "../repository/irepository.h"

class ParsingCommandGet : public IParsingCommandOut
{
public:
    ParsingCommandGet(const TShell *shell1, const IRepository* repository);
    virtual void        ParsingData();
};

#endif // PARSINGCOMMANDGET_H
