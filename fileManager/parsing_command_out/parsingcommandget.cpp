#include "parsingcommandget.h"

ParsingCommandGet::ParsingCommandGet()
{
    regExp.setPattern("(Cloning into ')(.*)(')(.*)");
}
//----------------------------------------------------------------------------------------/
void ParsingCommandGet::ParsingData()
{
    if(commandStart && !commandEnd)
    {
        // команда стартовала, но еще не завершилась
    }
    else if(!commandStart && commandEnd)
    {
        // команда завершилась
    }
    else
    {
        // ничего не делаем
    }
}
//----------------------------------------------------------------------------------------/

