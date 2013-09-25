#include "controller_repository.h"
#include <iostream>

using namespace GANN_MVC;
//----------------------------------------------------------------------------------------/
ControllerRepository::ControllerRepository( ):
    model(QSharedPointer<ModelQmlAndCRepository>(new ModelQmlAndCRepository()))
{

}
//----------------------------------------------------------------------------------------/
QVariantList ControllerRepository::GetListRepository()
{
    return model->GetListRepository();
}
//----------------------------------------------------------------------------------------/
void ControllerRepository::StartCloneRepository()
{
    std::cout<<"StartClone"<<std::endl;
}
//----------------------------------------------------------------------------------------/
void ControllerRepository::CancelCloneRepository()
{
    std::cout<<"CancelClone"<<std::endl;
}
//----------------------------------------------------------------------------------------/
