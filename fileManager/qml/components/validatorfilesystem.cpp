#include "validatorfilesystem.h"

//----------------------------------------------------------------------------------------/
ValidatorFileSystem::ValidatorFileSystem():
    QValidator()
{
}
//----------------------------------------------------------------------------------------/
QValidator::State ValidatorFileSystem::validate(QString &string, int &pos) const
{
    dir.setPath(string);
    if(dir.exists())
        return QValidator::Acceptable;
    else
        return QValidator::Invalid;
}
//----------------------------------------------------------------------------------------/


