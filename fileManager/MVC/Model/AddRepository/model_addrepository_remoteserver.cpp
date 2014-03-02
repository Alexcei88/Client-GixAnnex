#include "model_addrepository_remoteserver.h"

using namespace GANN_MVC;

//----------------------------------------------------------------------------------------/
ModelAddRepositoryRemoteServer::ModelAddRepositoryRemoteServer()
{}
//----------------------------------------------------------------------------------------/
QString ModelAddRepositoryRemoteServer::GetRemoteUrl(const QMap<QString, QString> &options) const
{
    return QString(options["Host name"] + "@" + options["User name"] + ":" + options["Directory"]);
}
//----------------------------------------------------------------------------------------/
