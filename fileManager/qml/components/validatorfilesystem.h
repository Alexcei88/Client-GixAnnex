#ifndef VALIDATORFILESYSTEM_H
#define VALIDATORFILESYSTEM_H

#include <QValidator>
#include <QDir>

class ValidatorFileSystem : public QValidator
{
public:
    ValidatorFileSystem();
    virtual State validate(QString &, int &) const;

private:
    mutable QDir dir;
};

#endif // VALIDATORFILESYSTEM_H
