#ifndef TREPOSITORY_H
#define TREPOSITORY_H
#include "irepository.h"

class TRepository : public IRepository
{
public:
    TRepository();
    TRepository(const QString& localUrl, const QString& remoteUrl, const QString& nameRepo);

    virtual ~TRepository();

    virtual GANN_DEFINE::RESULT_EXEC_PROCESS CloneRepository(const QString& localURL, const QString& nameRepo, const QString& remoteURL);
    virtual GANN_DEFINE::RESULT_EXEC_PROCESS DeleteRepository(const QString &localURL);
    virtual GANN_DEFINE::RESULT_EXEC_PROCESS GetContentFile(const QString& file = " ") const;
    virtual int         DropContentFile(const QString& file = " ") const;
    virtual int         WhereisFile(const QString& file = " ") const;

};

#endif // TREPOSITORY_H
