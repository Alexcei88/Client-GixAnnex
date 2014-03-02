#include "controlleraddrepository.h"

// model stuff
#include "../Model/AddRepository/model_addrepository_remoteserver.h"

using namespace GANN_MVC;
//----------------------------------------------------------------------------------------/
ControllerAddRepository::ControllerAddRepository()
{}
//----------------------------------------------------------------------------------------/
void ControllerAddRepository::setOptions(const QVariant key, const QVariant value)
{
    if(options.contains(key.toString()))
        options.remove(key.toString());
    options[key.toString()] = value.toString();
}
//----------------------------------------------------------------------------------------/
QVariant ControllerAddRepository::getOptions(const QVariant key)
{
    return options.contains(key.toString()) ? options[key.toString()] : "";
}
//----------------------------------------------------------------------------------------/
void ControllerAddRepository::selectServer(const QVariant index)
{
    options.clear();
    model.reset(new ModelAddRepositoryRemoteServer());
    options["Port"] = "22";
}
//----------------------------------------------------------------------------------------/
void ControllerAddRepository::startAddRepository() const
{
    assert(model.get());
    model->StartAddRepository(options);
}
//----------------------------------------------------------------------------------------/
void ControllerAddRepository::cancelAddRepository() const
{
    assert(model.get());
    model->CancelAddRepository(options);
}
//----------------------------------------------------------------------------------------/
void ControllerAddRepository::closeAddRepository() const
{
    IModelQmlAndCAddRepository::CloseWindowAddRepository();
}
//----------------------------------------------------------------------------------------/


