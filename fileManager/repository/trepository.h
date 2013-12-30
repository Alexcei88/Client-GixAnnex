#ifndef TREPOSITORY_H
#define TREPOSITORY_H
#include "irepository.h"

class TRepository : public IRepository
{
public:
    TRepository();
    TRepository(const QString& localUrl, const QString& remoteUrl, const QString& nameRepo);

    virtual ~TRepository();

    virtual GANN_DEFINE::RESULT_EXEC_PROCESS CloneRepository(QString& localURL, const QString& nameRepo, const QString& remoteURL);
    virtual GANN_DEFINE::RESULT_EXEC_PROCESS DeleteRepository();
    virtual GANN_DEFINE::RESULT_EXEC_PROCESS GetContentFile(const QString& file = " ", const bool mode = true);
    virtual GANN_DEFINE::RESULT_EXEC_PROCESS DropContentFile(const QString& file = " ");
    virtual GANN_DEFINE::RESULT_EXEC_PROCESS RemoveFile(const QString& file = " ");
    virtual GANN_DEFINE::RESULT_EXEC_PROCESS WhereisFile(const QString& file = " ");
    virtual GANN_DEFINE::RESULT_EXEC_PROCESS SyncRepository() const;
};

#endif // TREPOSITORY_H
