#include "imodel_addrepository.h"
#include "facadeapplication.h"

using namespace GANN_MVC;

//----------------------------------------------------------------------------------------/
IModelQmlAndCAddRepository::IModelQmlAndCAddRepository()
{}
//----------------------------------------------------------------------------------------/
GANN_DEFINE::RESULT_EXEC_PROCESS IModelQmlAndCAddRepository::StartAddRepository(const QMap<QString, QString> &options)
{
    const QString remoteUrl = GetRemoteUrl(options);
    const QString localUrl = GetLocalUrl(options);
    const QString nameRepository = GetNameRepository(options);

    return FacadeApplication::getInstance()->StartCloneRepository(localUrl, remoteUrl, nameRepository);
}
//----------------------------------------------------------------------------------------/
void IModelQmlAndCAddRepository::CancelAddRepository() const
{

}
//----------------------------------------------------------------------------------------/
void IModelQmlAndCAddRepository::CloseWindowAddRepository()
{
    FacadeApplication::getInstance()->systemTray->CloseAddRepository();
}
//----------------------------------------------------------------------------------------/
QString IModelQmlAndCAddRepository::GetRemoteUrl(const QMap<QString, QString>& options) const
{

}
//----------------------------------------------------------------------------------------/
QString IModelQmlAndCAddRepository::GetLocalUrl(const QMap<QString, QString>& options) const
{

}
//----------------------------------------------------------------------------------------/
QString IModelQmlAndCAddRepository::GetNameRepository(const QMap<QString, QString>& options) const
{

}
//----------------------------------------------------------------------------------------/



