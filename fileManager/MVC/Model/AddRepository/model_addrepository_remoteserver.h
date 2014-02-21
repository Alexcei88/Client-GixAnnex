#ifndef MODEL_ADDREPOSITORY_REMOTESERVER_H
#define MODEL_ADDREPOSITORY_REMOTESERVER_H

#include "imodel_addrepository.h"

namespace GANN_MVC
{
class ModeladdRepositoryRemoteServer: public IModelQmlAndCAddRepository
{
public:
    ModeladdRepositoryRemoteServer();

    virtual GANN_DEFINE::RESULT_EXEC_PROCESS StartAddRepository();

};
}

#endif // MODEL_ADDREPOSITORY_REMOTESERVER_H
