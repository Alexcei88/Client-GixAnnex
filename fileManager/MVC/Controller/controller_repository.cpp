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
QVariant ControllerRepository::getStateRepository(QUrl path) const
{
    return model->GetStateRepository(path.toString());
}
//----------------------------------------------------------------------------------------/
QVariant ControllerRepository::getDefaultRepositoryPath() const
{
    return model->GetDefaultRepository();
}
//----------------------------------------------------------------------------------------/
QVariant ControllerRepository::startCloneRepository(QVariant localUlr, QVariant remoteURL, QVariant nameRepo)
{
    return model->CloneRepository(localUlr.toString(), remoteURL.toString(), nameRepo.toString());
}
//----------------------------------------------------------------------------------------/
void ControllerRepository::cancelCloneRepository() const
{
    model->CancelCloneRepository();
}
//----------------------------------------------------------------------------------------/
QVariant ControllerRepository::getContentDirectory(QUrl dir) const
{
    return model->GetContentDirectory(dir.toString());
}
//----------------------------------------------------------------------------------------/
QVariant ControllerRepository::dropContentDirectory(QUrl dir) const
{
    return model->DropContentDirectory(dir.toString());
}
//----------------------------------------------------------------------------------------/
QVariant ControllerRepository::removeDirectory(QUrl dir) const
{
    return model->RemoveDirectory(dir.toString());
}
//----------------------------------------------------------------------------------------/
QVariant ControllerRepository::dirIsSubRootDirRepository(QUrl dir) const
{
    return model->DirIsSubRootDirRepository(dir.toLocalFile());
}
//----------------------------------------------------------------------------------------/
const QVariant ControllerRepository::getLastError() const
{
    return model->GetLastError();
}
//----------------------------------------------------------------------------------------/

