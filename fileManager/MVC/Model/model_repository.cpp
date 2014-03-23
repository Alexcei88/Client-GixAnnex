#include "model_repository.h"
#include "../facadeapplication.h"
#include "../shell/facade_shellcommand.h"

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
void ModelQmlAndCRepository::DeleteRepository(const QString& path) const
{
    auto iterRepo = FacadeApplication::instance->currentRepository;
    if(iterRepo != FacadeApplication::instance->repository.end())
    {
        FacadeApplication::instance->DeleteRepository(path);
        FacadeApplication::instance->systemTray->ReLoadListRepository();
    }
    else
    {
        ChangeCurrentRepository(path);
        FacadeApplication::instance->DeleteRepository(path);
        FacadeApplication::instance->systemTray->ReLoadListRepository();
    }
}
//----------------------------------------------------------------------------------------/
void ModelQmlAndCRepository::SetEnableRepository(bool enable)
{          
    auto iterRepo = FacadeApplication::instance->currentRepository;
    if(iterRepo != FacadeApplication::instance->repository.end())
    {
        IRepository* curRepo = iterRepo->second.get();
        // чистим список команд для вкл/выкл репозитория
        FacadeShellCommand::ClearCommandForRepository(curRepo);
        if(FacadeShellCommand::IsExecuteCommandForRepository(curRepo))
        {
            assert("У включаемого репозитория не должно быть в очереди команд" && enable == false);

            // фиксируем, что репозиторий будет выключен
            willEnableRepository = enable;
            connectionFacadeShellCommand = QObject::connect(FacadeShellCommand::GetInstance(), &FacadeShellCommand::FinishWaitCommand, [&]()
            {
                // меняем по истечению времени
                this->ChangeEnabledRepository(willEnableRepository, true);
            });
        }
        else
        {
            // сразу же меняем
            ChangeEnabledRepository(enable);
        }
    }
    else{
        assert("CurrentRepo is NULL" && false);
    }
}
//----------------------------------------------------------------------------------------/
bool ModelQmlAndCRepository::IsExecuteCommandForCurrentRepository() const
{
    auto iterRepo = FacadeApplication::instance->currentRepository;
    if(iterRepo != FacadeApplication::instance->repository.end()) {
        IRepository* curRepo = iterRepo->second.get();
        return FacadeShellCommand::IsExecuteCommandForRepository(curRepo);
    }
    else{
        assert("CurrentRepo is NULL" && false);
    }

}
//----------------------------------------------------------------------------------------/
GANN_DEFINE::RESULT_EXEC_PROCESS ModelQmlAndCRepository::CloneRepository(const QString& localURL, const QString& remoteURL, const QString& nameRepo)
{
    FacadeApplication *facade = FacadeApplication::getInstance();
    QString localPath = localURL;
    return facade->StartCloneRepository(localPath, remoteURL, nameRepo);
}
//----------------------------------------------------------------------------------------/
void ModelQmlAndCRepository::CancelCloneRepository(const bool breakCommand) const
{
  //  FacadeApplication::instance->systemTray->CancelCloneRepository();
}
//----------------------------------------------------------------------------------------/
GANN_DEFINE::RESULT_EXEC_PROCESS ModelQmlAndCRepository::GetContentDirectory(const QString& dir) const
{
    auto iterRepo = FacadeApplication::instance->currentRepository;
    if(iterRepo != FacadeApplication::instance->repository.end())
    {
        IRepository* curRepo = iterRepo->second.get();
        return curRepo->GetContentFile(dir, false);
    }
    else{
        assert("CurrentRepo is NULL" && false);
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
        return curRepo->DropContentFile(dir, false);
    }
    else{
        assert("CurrentRepo is NULL" && false);
    }
    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
GANN_DEFINE::RESULT_EXEC_PROCESS ModelQmlAndCRepository::RemoveDirectory(const QString& dir) const
{
    auto iterRepo = FacadeApplication::instance->currentRepository;
    if(iterRepo != FacadeApplication::instance->repository.end())
    {
        IRepository* curRepo = iterRepo->second.get();
        return curRepo->RemoveFile(dir);
    }
    else{
        assert("CurrentRepo is NULL" && false);
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
        curRepo->ChangeCurrentDirectory(dir);
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
const QString ModelQmlAndCRepository::GetLastModifiedFile(const QString &file)
{
    fileInfo.setFile(file);
    if(!fileInfo.isFile() && fileInfo.isSymLink())
    {
        return "undefined";
    }
    return fileInfo.lastModified().date().toString("dd.MM.yyyy");
}
//----------------------------------------------------------------------------------------/
const QString ModelQmlAndCRepository::GetSizeFile(const QString& file)
{
    fileInfo.setFile(file);
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
        _dir.setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::Files | QDir::System);
        _dir.setPath(file);
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
const QString ModelQmlAndCRepository::GetFullPathFileConfigRepositories() const
{
    const QString fileName = "ganx-repository.xml";
    const QString fullPath = QDir::homePath() + "/.config/GitAnnexClient/" + fileName;
    assert(QFile::exists(fullPath));
    return fullPath;
}
//----------------------------------------------------------------------------------------/
bool ModelQmlAndCRepository::GetDirectModeWorkRepositoryOfCurrentRepository() const
{
    auto iterRepo = FacadeApplication::instance->currentRepository;
    if(iterRepo != FacadeApplication::instance->repository.end())
    {
        IRepository* curRepo = iterRepo->second.get();
        return curRepo->GetDirectMode();
    }
    else{
        assert("CurrentRepo is NULL" && false);
        return false;
    }
}
//----------------------------------------------------------------------------------------/
QString ModelQmlAndCRepository::GetPathOfCurrentRepository() const
{
    auto iterRepo = FacadeApplication::instance->currentRepository;
    if(iterRepo != FacadeApplication::instance->repository.end())
    {
        IRepository* curRepo = iterRepo->second.get();
        return curRepo->GetLocalURL();
    }
    else{
        assert("CurrentRepo is NULL" && false);
        return "";
    }
}
//----------------------------------------------------------------------------------------/
bool ModelQmlAndCRepository::MovePathOfCurrentRepository() const
{
    auto iterRepo = FacadeApplication::instance->currentRepository;
    if(iterRepo != FacadeApplication::instance->repository.end())
    {
        IRepository* curRepo = iterRepo->second.get();
//        return curRepo->
    }
    else{
        assert("CurrentRepo is NULL" && false);
        return "";
    }
}
//----------------------------------------------------------------------------------------/
void ModelQmlAndCRepository::ChangeEnabledRepository(const bool enable, const bool hideWaitWindow) const
{
    auto iterRepo = FacadeApplication::instance->currentRepository;
    if(iterRepo != FacadeApplication::instance->repository.end())
    {
        IRepository* curRepo = iterRepo->second.get();
        enable ? curRepo->SetState(IRepository::Synced) : curRepo->SetState(IRepository::Disable_sincing);
        // пересохраняем настройки конфиг-файла
        FacadeApplication::instance->SaveOptionsRepository(iterRepo->second.get()->GetLocalURL());

        if(hideWaitWindow)
        {
            // нужно еще скрыть окно
            FacadeApplication::instance->systemTray->HideWindowWaitCommand();
        }
        // перезагружаем представление
        FacadeApplication::instance->systemTray->ReLoadListRepository();
        // даем команду обновить состояние иконок
        FacadeApplication::instance->ReleaseThreadSyncIcons();

        QObject::disconnect(connectionFacadeShellCommand);

    }
    else{
        assert("CurrentRepo is NULL" && false);
    }
}
//----------------------------------------------------------------------------------------/
