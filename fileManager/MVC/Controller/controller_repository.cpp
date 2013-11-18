#include "controller_repository.h"
#include "controller_icons.h"
#include <iostream>

using namespace GANN_MVC;
//----------------------------------------------------------------------------------------/
ControllerRepository::ControllerRepository( ):
    model(QSharedPointer<ModelQmlAndCRepository>(new ModelQmlAndCRepository()))
{
    QObject::connect(this, &ControllerRepository::currentPathRepoChanged, [=](QString dir){model->ChangeCurrentRepository(dir); });
}
//----------------------------------------------------------------------------------------/
QVariant ControllerRepository::GetStateRepository(QVariant path) const
{
    return model->GetStateRepository(path.toString());
}
//----------------------------------------------------------------------------------------/
QVariant ControllerRepository::GetDefaultRepositoryPath() const
{
    return model->GetDefaultRepository();
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
    model->CancelCloneRepository();
}
//----------------------------------------------------------------------------------------/
QVariant ControllerRepository::GetContentDirectory(QVariant dir) const
{
    return model->GetContentDirectory(dir.toString());
}
//----------------------------------------------------------------------------------------/
QVariant ControllerRepository::DropContentDirectory(QVariant dir) const
{
    return model->DropContentDirectory(dir.toString());
}
//----------------------------------------------------------------------------------------/
QVariant ControllerRepository::DirIsSubRootDirRepository(QVariant dir) const
{
    return model->DirIsSubRootDirRepository(dir.toString());
}
//----------------------------------------------------------------------------------------/
