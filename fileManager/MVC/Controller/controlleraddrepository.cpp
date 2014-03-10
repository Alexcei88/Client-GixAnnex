#include "controlleraddrepository.h"

// model stuff
#include "../Model/AddRepository/model_addrepository_remoteserver.h"
#include "../Model/AddRepository/model_addrepository_other.h"

using namespace GANN_MVC;
//----------------------------------------------------------------------------------------/
ControllerAddRepository::ControllerAddRepository()
{}
//----------------------------------------------------------------------------------------/
const QVariantList ControllerAddRepository::GetListOptions()
{
    if(!model) return QVariantList();
    return model->GetListOptions();
}
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
    switch(index.toInt())
    {
        // Cloud repository
        case 0: model.reset(new ModelAddRepositoryRemoteServer()); break;
        case 1: model.reset(new ModelAddRepositoryRemoteServer()); break;

        // Local repository
        case 30: model.reset(new ModelAddOtherRepository()); break;

        default:
            assert("Unknow index repository!!!" && 0);
    }
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
