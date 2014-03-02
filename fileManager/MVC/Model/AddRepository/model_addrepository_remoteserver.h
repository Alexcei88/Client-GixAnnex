#ifndef MODEL_ADDREPOSITORY_REMOTESERVER_H
#define MODEL_ADDREPOSITORY_REMOTESERVER_H

#include "imodel_addrepository.h"

namespace GANN_MVC
{
class ModelAddRepositoryRemoteServer: public IModelQmlAndCAddRepository
{
public:
    ModelAddRepositoryRemoteServer();

    virtual QString GetRemoteUrl(const QMap<QString, QString> &options) const;
};
}

#endif // MODEL_ADDREPOSITORY_REMOTESERVER_H
