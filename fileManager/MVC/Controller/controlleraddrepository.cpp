#include "controlleraddrepository.h"

// model stuff
#include "../Model/AddRepository/model_addrepository_remoteserver.h"

using namespace GANN_MVC;
//----------------------------------------------------------------------------------------/
ControllerAddRepository::ControllerAddRepository()
{}
//----------------------------------------------------------------------------------------/
void ControllerAddRepository::selectRemoteServer()
{
    //model.reset(new ModeladdRepositoryRemoteserver());
}
//----------------------------------------------------------------------------------------/
void ControllerAddRepository::closeAddRepository() const
{
    IModelQmlAndCAddRepository::CloseWindowAddRepository();
}
//----------------------------------------------------------------------------------------/


