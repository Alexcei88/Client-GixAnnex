// our stuff
#include "controller_repository.h"
#include "controller_icons.h"
#include "facadeapplication.h"

#include <iostream>

using namespace GANN_MVC;
//----------------------------------------------------------------------------------------/
ControllerRepository::ControllerRepository( ):
    model(QSharedPointer<ModelQmlAndCRepository>(new ModelQmlAndCRepository()))
{
    QObject::connect(this, &ControllerRepository::currentPathRepoChanged, [=](QUrl dir)
    {
        QMutex& mutex = FacadeApplication::threadModel.mutexSyncIcons;
        QMutexLocker mutexLocker(&mutex);
        // здесь захватить мьютексом поток синхронизации иконки
        model->ChangeCurrentRepository(dir.toLocalFile());
    });
}
//----------------------------------------------------------------------------------------/
QVariant ControllerRepository::getStateRepository(QUrl path) const
{
    return model->GetStateRepository(path.toString());
}
//----------------------------------------------------------------------------------------/
void ControllerRepository::deleteRepository(QUrl path) const
{
    model->DeleteRepository(path.toString());
}
//----------------------------------------------------------------------------------------/
void ControllerRepository::setEnableRepository(bool enable) const
{
    model->SetEnableRepository(enable);
}
//----------------------------------------------------------------------------------------/
bool ControllerRepository::isExecuteCommandForCurrentRepository() const
{
    return model->IsExecuteCommandForCurrentRepository();
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
const QVariant ControllerRepository::GetPathRepoConfig() const
{
    return model->GetFullPathFileConfigRepositories();
}
//----------------------------------------------------------------------------------------/

