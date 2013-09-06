#include "parsingcommandclone.h"

//----------------------------------------------------------------------------------------/
ParsingCommandClone::ParsingCommandClone(): IParsingCommandOut()
{
//    regExp.setPattern("(Cloning into) (\'(*))(\')(*)");
    regExp.setPattern("(Cloning into ')(.*)(')(.*)");

}
//----------------------------------------------------------------------------------------/
void ParsingCommandClone::ParsingData()
{
    if(!commandStart && commandEnd && !dataStdOut.empty())
    {
        // выполняем парсинг
        dataAfterParsing.clear();
        const QString str = dataStdOut.at(0);
        if(regExp.indexIn(str) != -1)
        {
            const QString nameFolder = regExp.cap(2);
            dataAfterParsing << nameFolder;
        }
    }
    // иначе ничего не делаем
}
//----------------------------------------------------------------------------------------/

