#ifndef TREPOSITORY_H
#define TREPOSITORY_H
#include "irepository.h"

class TRepository : public IRepository
{
public:
    TRepository();
    virtual ~TRepository();

    virtual int         CloneRepository(const QString &nameRepo, const QString &remoteURL, const QString &localURL);
    virtual int         DeleteRepository(const QString &localURL);
    virtual int         GetContentFile(const QString& file = " ") const;
    virtual int         DropContentFile(const QString& file = " ") const;
    virtual int         WhereisFile(const QString& file = " ") const;

};

#endif // TREPOSITORY_H
