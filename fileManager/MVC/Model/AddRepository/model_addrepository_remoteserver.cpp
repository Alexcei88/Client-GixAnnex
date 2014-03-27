#include "model_addrepository_remoteserver.h"

using namespace GANN_MVC;

//----------------------------------------------------------------------------------------/
ModelAddRepositoryRemoteServer::ModelAddRepositoryRemoteServer()
    : IModelQmlAndCAddRepository()
{
    listOptions << "Host name" << "User name" << "Directory"<<"Port"<< "Destinition URL" << "Name";
}
//----------------------------------------------------------------------------------------/
QString ModelAddRepositoryRemoteServer::GetRemoteUrl(const QMap<QString, QString> &options) const
{
    return QString(options["User name"] + "@" + options["Host name"] + ":" + options["Directory"]);
}
//----------------------------------------------------------------------------------------/
