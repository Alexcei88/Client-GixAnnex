#ifndef PARSINGCOMMANDCLONE_H
#define PARSINGCOMMANDCLONE_H

#include "iparsingcommandout.h"

class ParsingCommandClone : public IParsingCommandOut
{
public:
    ParsingCommandClone(IRepository* repository);
    virtual void        ParsingData();

private:
    /** @brief список регулярных выражений для парсинга данных */
    QStringList         listRegExpPossible;

    /** @brief класс парсинга*/
    QRegExp             regExp;
};

#endif // PARSINGCOMMANDCLONE_H
