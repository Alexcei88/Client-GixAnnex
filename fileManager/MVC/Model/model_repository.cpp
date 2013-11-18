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
    QString localPath = "";
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
const QString ModelQmlAndCRepository::GetLastModifiedFile(const QString& file) const
{
    auto iterRepo = FacadeApplication::instance->currentRepository;
    if(iterRepo != FacadeApplication::instance->repository.end())
    {
        IRepository* curRepo = iterRepo->second.get();
        QMap<QString, IRepository::PARAMETR_FILEFOLDER_GIT_ANNEX> mapState = curRepo->GetStateFileDir();
        const QFileInfo& fileInfo = mapState[file].fileInfo;
        return fileInfo.lastModified().date().toString("dd.MM.yyyy");
    }
    else{
        assert("CurrentRepo is NULL" && false);
    }
}
//----------------------------------------------------------------------------------------/
const QString ModelQmlAndCRepository::GetSizeFile(const QString& file) const
{
    auto iterRepo = FacadeApplication::instance->currentRepository;
    if(iterRepo != FacadeApplication::instance->repository.end())
    {
        IRepository* curRepo = iterRepo->second.get();
        const QMap<QString, IRepository::PARAMETR_FILEFOLDER_GIT_ANNEX> mapState = curRepo->GetStateFileDir();
        const QFileInfo& fileInfo = mapState[file].fileInfo;
        if(fileInfo.isFile())
        {
            quint64 nSize = fileInfo.size();
            qint64 i = 0;
            for (; nSize > 1023; nSize /= 1024, ++i) { }
            return QString().setNum(nSize) + " " + "BKMGT"[i];
        }
        else
        {
            static QDir _dir;
            _dir.setPath(fileInfo.dir().absolutePath() + "/" + file);
            assert(_dir.exists());
            // возвращаем сколько коренных item-ов в поддиректории
            QStringList list = _dir.entryList();
            list.removeAll(".");
            list.removeAll("..");
            return QString().setNum(list.size()) + " " + "items";
        }
    }
    else{
        assert("CurrentRepo is NULL" && false);
    }
}
//----------------------------------------------------------------------------------------/


