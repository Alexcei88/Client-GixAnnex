#include "controller_repository.h"
#include "controller_icons.h"
#include <iostream>

using namespace GANN_MVC;
//----------------------------------------------------------------------------------------/
ControllerRepository::ControllerRepository( ):
    model(QSharedPointer<ModelQmlAndCRepository>(new ModelQmlAndCRepository()))
{
    QObject::connect(this, &ControllerRepository::currentPathRepoChanged, [=](QUrl dir){model->ChangeCurrentRepository(dir.toLocalFile()); });
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
    return model->CloneRepository(localUlr.toString(), remoteURL.toString(), nameRepo.toString());
}
//----------------------------------------------------------------------------------------/
void ControllerRepository::CancelCloneRepository() const
{
    model->CancelCloneRepository();
}
//----------------------------------------------------------------------------------------/
QVariant ControllerRepository::GetContentDirectory(QUrl dir) const
{
    return model->GetContentDirectory(dir.toLocalFile());
}
//----------------------------------------------------------------------------------------/
QVariant ControllerRepository::DropContentDirectory(QUrl dir) const
{
    return model->DropContentDirectory(dir.toLocalFile());
}
//----------------------------------------------------------------------------------------/
QVariant ControllerRepository::DirIsSubRootDirRepository(QVariant dir) const
{
    return model->DirIsSubRootDirRepository(dir.toString());
}
//----------------------------------------------------------------------------------------/
const QVariant ControllerRepository::GetLastError() const
{
    return model->GetLastError();
}
//----------------------------------------------------------------------------------------/

