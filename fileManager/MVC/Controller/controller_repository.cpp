#include "controller_repository.h"
#include <iostream>

using namespace GANN_MVC;
//----------------------------------------------------------------------------------------/
ControllerRepository::ControllerRepository( ):
    model(QSharedPointer<ModelQmlAndCRepository>(new ModelQmlAndCRepository()))
{
   // emit signalUpdateListRepository();
}
//----------------------------------------------------------------------------------------/
QVariantList ControllerRepository::GetListRepository() const
{
    return model->GetListRepository();
}
//----------------------------------------------------------------------------------------/
QVariant ControllerRepository::StartCloneRepository(QVariant localUlr, QVariant remoteURL, QVariant nameRepo)
{
    QVariant result = model->CloneRepository(localUlr.toString(), remoteURL.toString(), nameRepo.toString());
    return result;
}
//----------------------------------------------------------------------------------------/
void ControllerRepository::CancelCloneRepository() const
{
    std::cout<<"Cancel Clone Repository"<<std::endl;
    model->CancelCloneRepository();
}
//----------------------------------------------------------------------------------------/
