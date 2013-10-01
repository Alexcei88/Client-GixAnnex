#include "model_repository.h"

#include <QVariantList>

using namespace GANN_MVC;
using namespace GANN_DEFINE;

//----------------------------------------------------------------------------------------/
ModelQmlAndCRepository::ModelQmlAndCRepository()
{
    GetListRepository();
}
//----------------------------------------------------------------------------------------/
QVariantList ModelQmlAndCRepository::GetListRepository()
{
    QVariantList repoRegistry;
    std::map<QString, boost::shared_ptr<IRepository>> repository = FacadeApplication::getInstance()->repository;
    // заполняем repoRegistry
    for(auto i = repository.begin(); i != repository.end(); ++i)
    {
        const QVariant pathRepo = i->first;
        repoRegistry.push_back(pathRepo);
    }
    return repoRegistry;
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
        facade->ReLoadListRepository();
        facade->CancelCloneRepository();
    }
    return result;
}
//----------------------------------------------------------------------------------------/
void ModelQmlAndCRepository::CancelCloneRepository(bool breakCommand)
{
    FacadeApplication::getInstance()->CancelCloneRepository(breakCommand);
}
//----------------------------------------------------------------------------------------/
GANN_DEFINE::RESULT_EXEC_PROCESS ModelQmlAndCRepository::GetContentDirectory(const QString& dir) const
{

}
//----------------------------------------------------------------------------------------/
void ModelQmlAndCRepository::ChangeCurrentRepository(const QString& dir) const
{
    FacadeApplication::getInstance()->ChangeCurrentRepository(dir);
}
//----------------------------------------------------------------------------------------/


