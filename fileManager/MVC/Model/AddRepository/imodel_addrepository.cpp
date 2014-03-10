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
QVariantList IModelQmlAndCAddRepository::GetListOptions() const
{
    return listOptions;
}
//----------------------------------------------------------------------------------------/
void IModelQmlAndCAddRepository::CancelAddRepository(const QMap<QString, QString> &options) const
{
    Q_UNUSED(options);
}
//----------------------------------------------------------------------------------------/
void IModelQmlAndCAddRepository::CloseWindowAddRepository()
{
    FacadeApplication::getInstance()->systemTray->CloseAddRepository();
}
//----------------------------------------------------------------------------------------/
QString IModelQmlAndCAddRepository::GetRemoteUrl(const QMap<QString, QString>& options) const
{
    return options.contains("Source URL") ? options["Source URL"] : "";
}
//----------------------------------------------------------------------------------------/
QString IModelQmlAndCAddRepository::GetLocalUrl(const QMap<QString, QString>& options) const
{
    return options.contains("Destinition URL") ? options["Destinition URL"] : "";
}
//----------------------------------------------------------------------------------------/
QString IModelQmlAndCAddRepository::GetNameRepository(const QMap<QString, QString>& options) const
{
    return options.contains("Name") ? options["Name"] : "";
}
//----------------------------------------------------------------------------------------/



