#include "model_repository.h"

#include "../facadeapplication.h"
#include "../repository/irepository.h"

using namespace GANN_MVC;
using namespace GANN_DEFINE;

#include <QIcon>
#include <QStringList>

//----------------------------------------------------------------------------------------/
ModelQmlAndCRepository::ModelQmlAndCRepository()
{
}
//----------------------------------------------------------------------------------------/
const QString ModelQmlAndCRepository::GetDefaultRepository() const
{
    QString localPath = "";
    if(FacadeApplication::instance->currentRepository != FacadeApplication::instance->repository.end())
    {
        localPath = FacadeApplication::instance->currentRepository->first;
    }
    return localPath;
}
//----------------------------------------------------------------------------------------/
const QString ModelQmlAndCRepository::GetStateRepository(const QString& path) const
{
    auto iterator = FacadeApplication::instance->repository.find(path);
    assert(iterator != FacadeApplication::instance->repository.end());
    const IRepository* repository = iterator->second.get();
    return repository->GetState();
}
//----------------------------------------------------------------------------------------/
GANN_DEFINE::RESULT_EXEC_PROCESS ModelQmlAndCRepository::CloneRepository(const QString& localURL, const QString& remoteURL, const QString& nameRepo)
{
    FacadeApplication *facade = FacadeApplication::getInstance();
    QString localPath = localURL;
    GANN_DEFINE::RESULT_EXEC_PROCESS result =  facade->StartCloneRepository(localPath, remoteURL, nameRepo);
    if(result == NO_ERROR)
    {
        facade->SaveRepository(localPath, remoteURL, nameRepo);
        facade->systemTray->ReLoadListRepository();
        facade->systemTray->CancelCloneRepository();
    }
    return result;
}
//----------------------------------------------------------------------------------------/
void ModelQmlAndCRepository::CancelCloneRepository(bool breakCommand) const
{
    FacadeApplication::instance->systemTray->CancelCloneRepository();
}
//----------------------------------------------------------------------------------------/
GANN_DEFINE::RESULT_EXEC_PROCESS ModelQmlAndCRepository::GetContentDirectory(const QString& dir) const
{
    auto iterRepo = FacadeApplication::instance->currentRepository;
    if(iterRepo != FacadeApplication::instance->repository.end())
    {
        IRepository* curRepo = iterRepo->second.get();
        return curRepo->GetContentFile(dir);
    }
    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
GANN_DEFINE::RESULT_EXEC_PROCESS ModelQmlAndCRepository::DropContentDirectory(const QString& dir) const
{
    auto iterRepo = FacadeApplication::instance->currentRepository;
    if(iterRepo != FacadeApplication::instance->repository.end())
    {
        IRepository* curRepo = iterRepo->second.get();
        return curRepo->DropContentFile(dir);
    }
    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
void ModelQmlAndCRepository::ChangeCurrentRepository(const QString& dir) const
{
    FacadeApplication::instance->ChangeCurrentRepository(dir);
}
//----------------------------------------------------------------------------------------/


