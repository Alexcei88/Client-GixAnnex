#include "model_repository.h"
#include "../facadeapplication.h"

using namespace GANN_MVC;
using namespace GANN_DEFINE;

#include <QIcon>
#include <QStringList>
#include <QFileInfo>
#include <QDateTime>
#include <QDir>

//----------------------------------------------------------------------------------------/
ModelQmlAndCRepository::ModelQmlAndCRepository()
{}
//----------------------------------------------------------------------------------------/
const QString ModelQmlAndCRepository::GetDefaultRepository() const
{
    QString localPath = "/Empty";
    if(FacadeApplication::instance->currentRepository != FacadeApplication::instance->repository.end())
    {
        localPath = FacadeApplication::instance->currentRepository->first;
    }
    return localPath;
}
//----------------------------------------------------------------------------------------/
const QString ModelQmlAndCRepository::GetStateRepository(const QString& path) const
{
    auto iterator = FacadeApplication::instance->repository.find(path);
    assert(iterator != FacadeApplication::instance->repository.end());
    const IRepository* repository = iterator->second.get();
    return repository->GetState();
}
//----------------------------------------------------------------------------------------/
GANN_DEFINE::RESULT_EXEC_PROCESS ModelQmlAndCRepository::CloneRepository(const QString& localURL, const QString& remoteURL, const QString& nameRepo)
{
    FacadeApplication *facade = FacadeApplication::getInstance();
    QString localPath = localURL;
    GANN_DEFINE::RESULT_EXEC_PROCESS result =  facade->StartCloneRepository(localPath, remoteURL, nameRepo);
    if(result == NO_ERROR)
    {
        facade->SaveRepository(localPath, remoteURL, nameRepo);
        facade->systemTray->ReLoadListRepository();
        facade->systemTray->CancelCloneRepository();       
    }
    return result;
}
//----------------------------------------------------------------------------------------/
void ModelQmlAndCRepository::CancelCloneRepository(const bool breakCommand) const
{
    FacadeApplication::instance->systemTray->CancelCloneRepository();
}
//----------------------------------------------------------------------------------------/
GANN_DEFINE::RESULT_EXEC_PROCESS ModelQmlAndCRepository::GetContentDirectory(const QString& dir) const
{
    auto iterRepo = FacadeApplication::instance->currentRepository;
    if(iterRepo != FacadeApplication::instance->repository.end())
    {
        IRepository* curRepo = iterRepo->second.get();
        return curRepo->GetContentFile(dir);
    }
    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
GANN_DEFINE::RESULT_EXEC_PROCESS ModelQmlAndCRepository::DropContentDirectory(const QString& dir) const
{
    std::cout<<dir.toStdString().c_str()<<std::endl;
    auto iterRepo = FacadeApplication::instance->currentRepository;
    if(iterRepo != FacadeApplication::instance->repository.end())
    {
        IRepository* curRepo = iterRepo->second.get();
        return curRepo->DropContentFile(dir);
    }
    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
void ModelQmlAndCRepository::ChangeCurrentRepository(const QString& dir) const
{
    FacadeApplication::instance->ChangeCurrentRepository(dir);
}
//----------------------------------------------------------------------------------------/
void ModelQmlAndCRepository::ChangeCurrentViewDirectory(const QString &dir) const
{
    auto iterRepo = FacadeApplication::instance->currentRepository;
    if(iterRepo != FacadeApplication::instance->repository.end())
    {
        IRepository* curRepo = iterRepo->second.get();
        curRepo->UpdateParamSyncFileDirFull(dir);
    }
}
//----------------------------------------------------------------------------------------/
const QMap<QString, IRepository::PARAMETR_FILEFOLDER_GIT_ANNEX> &ModelQmlAndCRepository::GetParamSyncFileDir() const
{
    auto iterRepo = FacadeApplication::instance->currentRepository;
    if(iterRepo != FacadeApplication::instance->repository.end())
    {
        IRepository* curRepo = iterRepo->second.get();
        return curRepo->GetStateFileDir();
    }
    else{
        assert("CurrentRepo is NULL" && false);
    }
}
//----------------------------------------------------------------------------------------/
const QString ModelQmlAndCRepository::GetLastModifiedFile(const QUrl& file) const
{
    const QFileInfo fileInfo(file.toString());
    if(!fileInfo.isFile() && fileInfo.isSymLink())
    {
        return "undefined";
    }
    return fileInfo.lastModified().date().toString("dd.MM.yyyy");
}
//----------------------------------------------------------------------------------------/
const QString ModelQmlAndCRepository::GetSizeFile(const QUrl& file) const
{
    const QFileInfo fileInfo(file.toString());
    if(fileInfo.isFile())
    {
        quint64 nSize = fileInfo.size();
        qint64 i = 0;
        for (; nSize > 1023; nSize /= 1024, ++i) { }
        return QString().setNum(nSize) + " " + "BKMGT"[i];
    }
    else if(fileInfo.isSymLink())
    {
        // пустая ссылка
        return "undefined";
    }
    else
    {
        static QDir _dir;
        _dir.setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);
        _dir.setPath(file.toString());
        assert(_dir.exists());
        // возвращаем сколько коренных item-ов в поддиректории
        return QString().setNum(_dir.count()) + " " + "items";
    }
}
//----------------------------------------------------------------------------------------/
bool ModelQmlAndCRepository::DirIsSubRootDirRepository(const QString& dir) const
{
    auto iterRepo = FacadeApplication::instance->currentRepository;
    if(iterRepo != FacadeApplication::instance->repository.end())
    {
        const IRepository* curRepo = iterRepo->second.get();
        return curRepo->DirIsSubRootDirRepository(dir);
    }
    return false;
}
//----------------------------------------------------------------------------------------/
const QString& ModelQmlAndCRepository::GetLastError() const
{
    return FacadeApplication::getInstance()->lastError;
}
//----------------------------------------------------------------------------------------/

