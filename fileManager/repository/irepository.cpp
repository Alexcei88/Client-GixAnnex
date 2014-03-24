#include "irepository.h"
#include "analyze_execute_command/facadeanalyzecommand.h"
#include "utils/utils.h"
#include "facadeapplication.h"

// boost stuff
#include <boost/make_shared.hpp>

using namespace GANN_DEFINE;
using namespace AnalyzeCommand;

//----------------------------------------------------------------------------------------/
IRepository::IRepository()
{
    InitClass();
}
//----------------------------------------------------------------------------------------/
IRepository::IRepository(const QString& localUrl, const QString& remoteUrl, const QString& nameRepo):
   remoteURL(remoteUrl)
  ,localURL(localUrl)
  ,nameRepo(nameRepo)
{
    InitClass();
}
//----------------------------------------------------------------------------------------/
void IRepository::InitClass()
{
    shellCommand = boost::make_shared<ShellCommand>();

    facadeAnalyzeCommand = boost::make_shared<FacadeAnalyzeCommand>(this);

    // устанавливаем состояние репозитория по умолчанию
    paramRepo.autosync = true;
    paramRepo.autosyncContent = true;
    paramRepo.currentState = "Synced";

    // init Q_Enums
    const QMetaObject &mo = staticMetaObject;
    int enum_index = mo.indexOfEnumerator("STATE_REPOSITORY");
    metaEnumState = mo.enumerator(enum_index);

    int enum_indexF = mo.indexOfEnumerator("STATE_FILE_AND_DIR");
    metaEnumStateF = mo.enumerator(enum_indexF);

    // сигналы/слоты
    InitSignalAndSlots();

    dir.setPath("");
    dir.setFilter(QDir::NoDotAndDotDot | QDir::AllEntries | QDir::System);
}
//----------------------------------------------------------------------------------------/
void IRepository::InitSignalAndSlots()
{
    // сигналы/слоты
    //----------------------------------------------------------------------------------------/

    // подсоединяем watcher к нашим слотам
    QObject::connect(&watcher, SIGNAL(directoryChanged(QString)), this, SLOT(OnDirectoryChanged(QString)));
    QObject::connect(&watcher, SIGNAL(fileChanged(QString)), this, SLOT(OnFileChanged(QString)));
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS IRepository::StartWatchRepository()
{
    // запускаем watcher за репозиторием
    // за всеми каталогами, в том числе и поддиректориями
    QStringList listPath;
    GetListDirectoriesOnDirectory(localURL, listPath);
    watcher.addPaths(listPath);

    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
GANN_DEFINE::RESULT_EXEC_PROCESS IRepository::CopyFileToOtherRepository(const QString& file, const QString& nameRepository)
{
    shellCommand->SetWorkingDirectory(localURL);
    RESULT_EXEC_PROCESS result = shellCommand->CopyFileToOtherRepository(file, nameRepository);
    if(result != NO_ERROR)
    {
        printf("Error CopyFile");
        return result;
    }
    return result;
}
//----------------------------------------------------------------------------------------/
GANN_DEFINE::RESULT_EXEC_PROCESS IRepository::MoveFileToOtherRepository(const QString& file, const QString& nameRepository)
{
    shellCommand->SetWorkingDirectory(localURL);
    RESULT_EXEC_PROCESS result = shellCommand->MoveFileToOtherRepository(file, nameRepository);
    if(result != NO_ERROR)
    {
        printf("Error MoveFile");
        return result;
    }
    return result;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS IRepository::StopWatchRepository()
{
    QStringList listPath;
    GetListDirectoriesOnDirectory(localURL, listPath);
    watcher.removePaths(listPath);
    return NO_ERROR;
}
//----------------------------------------------------------------------------------------/
GANN_DEFINE::RESULT_EXEC_PROCESS IRepository::SetDirectMode(const bool& direct)
{
    shellCommand->SetWorkingDirectory(localURL);
    RESULT_EXEC_PROCESS result = shellCommand->SetDirectMode(direct, facadeAnalyzeCommand.get());
    if(result != NO_ERROR)
    {
        printf("Error SetDirectMode repositories: %s \n", localURL.toStdString().c_str());
        return result;
    }
    return result;
}
//----------------------------------------------------------------------------------------/
GANN_DEFINE::RESULT_EXEC_PROCESS IRepository::GetInfo() const
{
    shellCommand->SetWorkingDirectory(localURL);
    RESULT_EXEC_PROCESS result = shellCommand->GetInfoRepository(facadeAnalyzeCommand.get());
    if(result != NO_ERROR)
    {
        printf("Error Info repositories: %s \n", localURL.toStdString().c_str());
        return result;
    }
    return result;
}
//----------------------------------------------------------------------------------------/
void IRepository::SetState(const STATE_REPOSITORY& state)
{
    if(state == Disable_sincing)
    {
        // репозитория отключен, никаких дейтсвия выполнить над ним нельзя
        // слежение за ним тоже надо отключать
        paramRepo.autosync = false;
    }
    else if(state == Synced)
    {
        paramRepo.autosync = true;
    }
    QByteArray str = metaEnumState.valueToKey(int(state));
    paramRepo.currentState = QString(str);
}
//----------------------------------------------------------------------------------------/
QString IRepository::GetState() const
{
    return paramRepo.currentState;
}
//----------------------------------------------------------------------------------------/
void IRepository::SetStateFileDir(const QString& fileDirName, const STATE_FILE_AND_DIR &state)
{
    PARAMETR_FILEFOLDER_GIT_ANNEX& paramCurFile = paramSyncFileDir[fileDirName];
    QByteArray str = metaEnumStateF.valueToKey(int(state));
    paramCurFile.currentState = QString(str);
}
//----------------------------------------------------------------------------------------/
QString IRepository::GetStateFileDir(const QString& fileDirName) const
{
    const PARAMETR_FILEFOLDER_GIT_ANNEX& paramCurFile = paramSyncFileDir[fileDirName];
    return paramCurFile.currentState;
}
//----------------------------------------------------------------------------------------/
void IRepository::SetParamSyncRepository(const bool& autosync, const bool& autosyncContent)
{
    paramRepo.autosync = autosync;
    paramRepo.autosyncContent = autosyncContent;
}
//----------------------------------------------------------------------------------------/
void IRepository::ChangeCurrentDirectory(const QString& curDir)
{
    // проверка на то, что текущий путь является поддиректорией к корню репозитория
    assert(curDir.length() >= localURL.length() && curDir.contains(localURL, Qt::CaseSensitive));
    dir.setPath(curDir);

    // устанавливаем новый путь в фасаде анализа хода выполнения команд
    facadeAnalyzeCommand->SetCurrentPathRepository(curDir);

    paramSyncFileDir.clear();
    QStringList nameAllFilesAndDir = dir.entryList();
    for(auto iterator = nameAllFilesAndDir.begin(); iterator != nameAllFilesAndDir.end(); ++iterator)
    {
        PARAMETR_FILEFOLDER_GIT_ANNEX paramTemp;
        paramTemp.autosync = true;
        paramTemp.currentState = CalculateStateFileDir(*iterator);

        paramSyncFileDir[*iterator] = paramTemp;
    }
}
//----------------------------------------------------------------------------------------/
void IRepository::UpdateParamSyncFileDir()
{
    facadeAnalyzeCommand->ExecuteAddActionForAnalizeCommand();

    paramSyncFileDir.clear();
    QStringList nameAllFilesAndDir = dir.entryList();
    for(auto iterator = nameAllFilesAndDir.begin(); iterator != nameAllFilesAndDir.end(); ++iterator)
    {
        PARAMETR_FILEFOLDER_GIT_ANNEX paramTemp;
        paramTemp.autosync = true;
        paramTemp.currentState = CalculateStateFileDir(*iterator);

        paramSyncFileDir[*iterator] = paramTemp;
    }
}
//----------------------------------------------------------------------------------------/
bool IRepository::DirIsSubRootDirRepository(const QString& dir) const
{
    return (dir.length() >= localURL.length() && dir.contains(localURL, Qt::CaseSensitive));
}
//----------------------------------------------------------------------------------------/
QString IRepository::CalculateStateFileDir(const QString& file) const
{
    // текущее состояние
    QByteArray curState;
    if(paramRepo.currentState == metaEnumState.valueToKey(Disable_sincing))
    {
        curState = metaEnumStateF.valueToKey(Disable_sincingF);
    }
    else if(facadeAnalyzeCommand->IsErrorDroppingContentFileDir(file) || facadeAnalyzeCommand->IsErrorGettingContentFileDir(file))
    {
        curState = metaEnumStateF.valueToKey(SyncedFError);
    }
    else if(facadeAnalyzeCommand->IsGettingContentFileDir(file) || facadeAnalyzeCommand->IsDroppingContentFileDir(file))
    {
        curState = metaEnumStateF.valueToKey(SyncingF);
    }
    else
    {
        curState = metaEnumStateF.valueToKey(SyncedF);
    }
    return QString(curState);
}
//----------------------------------------------------------------------------------------/
void IRepository::GetListDirectoriesOnDirectory(const QString &path, QStringList& listDirectory)
{
    QDir dir(path);
    dir.setFilter(QDir::NoDotAndDotDot | QDir::AllDirs | QDir::System);
    QFileInfo fileInfo(path);

    if(fileInfo.isDir())
    {
        listDirectory << path;
        QStringList list = dir.entryList();
        for(QString& str : list)
        {
            GetListDirectoriesOnDirectory(Utils::CatDirFile(path, str), listDirectory);
        }
    }
    else
    {}
}
//----------------------------------------------------------------------------------------/
void IRepository::OnErrorCloneRepository(const QString &error)
{
    // здесь мы должны удалить репозитории, тк он не создался
    lastError = error;
}
//----------------------------------------------------------------------------------------/
void IRepository::OnSuccessfullyCloneRepository(const QString& folder)
{
    this->nameRepo = nameRepo;
    this->remoteURL = remoteURL;
    this->localURL  = localURL + "/" + folder;

    shellCommand->SetWorkingDirectory(localURL);

    RESULT_EXEC_PROCESS result = shellCommand->InitRepositories(nameRepo, facadeAnalyzeCommand.get());
    if(result != NO_ERROR)
    {
        printf("Error git-annex init repositories: %s \n", localURL.toStdString().c_str());
    }
}
//----------------------------------------------------------------------------------------/
//    СЛУЖЕБНЫЕ СЛОТЫ
//----------------------------------------------------------------------------------------/
void IRepository::OnChangeDirectMode(const bool mode)
{
    paramRepo.directMode = mode;
}
//----------------------------------------------------------------------------------------/
void IRepository::OnErrorChangeDirectMode(const QString& error)
{
#ifdef DEBUG
    std::cout<<"WARNING: Change Direct Mode return error!!!"<<std::endl;
#endif
}
//----------------------------------------------------------------------------------------/
void IRepository::OnDirectoryChanged(const QString& path)
{
#ifdef DEBUG
    std::cout<<"Change directory: "<<path.toStdString()<<std::endl;
#endif
    // даем команду потоку синхронизации на выполнение синхронизации
    FacadeApplication::getInstance()->ReleaseThreadSyncIcons();
}
//----------------------------------------------------------------------------------------/
void IRepository::OnFileChanged(const QString& path)
{
#ifdef DEBUG
    std::cout<<"Change file: "<<path.toStdString()<<std::endl;
#endif
    // даем команду потоку синхронизации на выполнение синхронизации
    FacadeApplication::getInstance()->ReleaseThreadSyncIcons();
}
//----------------------------------------------------------------------------------------/


