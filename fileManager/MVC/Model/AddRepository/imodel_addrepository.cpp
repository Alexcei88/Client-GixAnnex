#include "imodel_addrepository.h"
#include "facadeapplication.h"

using namespace GANN_MVC;

//----------------------------------------------------------------------------------------/
IModelQmlAndCAddRepository::IModelQmlAndCAddRepository()
{}
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



