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
};

#endif // TREPOSITORY_H
