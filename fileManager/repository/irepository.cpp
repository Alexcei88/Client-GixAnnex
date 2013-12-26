#include "irepository.h"
#include "analyze_execute_command/facadeanalyzecommand.h"

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

    facadeAnalyzeCommand = boost::make_shared<FacadeAnalyzeCommand>();

    // устанавливаем состояние репозитория по умолчанию
    paramRepo.autosync = true;
    paramRepo.autosyncContent = true;
    paramRepo.currentState = "Synced";
    paramRepo.directMode = true;

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
    QObject::connect(this, &IRepository::errorCloneRepository, this, &IRepository::OnErrorCloneRepository, Qt::DirectConnection);
    QObject::connect(this, &IRepository::changeDirectMode, this, &IRepository::OnChangeDirectMode, Qt::DirectConnection);
    //----------------------------------------------------------------------------------------/
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS IRepository::StartWatchRepository() const
{
    RESULT_EXEC_PROCESS result = shellCommand->WatchRepository(localURL);
    if(result != NO_ERROR)
    {
        printf("Error watch repositories: %s \n", localURL.toStdString().c_str());
        return result;
    }
    return result;
}
//----------------------------------------------------------------------------------------/
RESULT_EXEC_PROCESS IRepository::StopWatchRepository() const
{
    RESULT_EXEC_PROCESS result = shellCommand->WatchRepository(localURL, false);
    if(result != NO_ERROR)
    {
        printf("Error watch repositories: %s \n", localURL.toStdString().c_str());
        return result;
    }
    return result;
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
    for(auto iterator = nameAllFilesAndDir.begin(); iterator !=  nameAllFilesAndDir.end(); ++iterator)
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
    for(auto iterator = paramSyncFileDir.begin(); iterator !=  paramSyncFileDir.end(); ++iterator)
    {
        iterator.value().currentState = CalculateStateFileDir(iterator.key());
    }
}
//----------------------------------------------------------------------------------------/
bool IRepository::DirIsSubRootDirRepository(const QString& dir) const
{
    return (dir.length() >= localURL.length() && dir.contains(localURL, Qt::CaseSensitive) );
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
//    СЛУЖЕБНЫЕ СЛОТЫ
//----------------------------------------------------------------------------------------/
void IRepository::OnErrorCloneRepository(const QString &error)
{
    lastError = error;
}
//----------------------------------------------------------------------------------------/
void IRepository::OnChangeDirectMode(const bool mode)
{
    assert(paramRepo.directMode != mode);
    paramRepo.directMode = mode;
}
//----------------------------------------------------------------------------------------/
void IRepository::OnErrorChangeDirectMode(const QString& error)
{

}
//----------------------------------------------------------------------------------------/

