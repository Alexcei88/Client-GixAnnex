#include "irepository.h"

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

    const QMetaObject &mo = staticMetaObject;
    int enum_index = mo.indexOfEnumerator("STATE_REPOSITORY");
    metaEnumState = mo.enumerator(enum_index);

    // устанавливаем состояние репозитория по умолчанию
    paramSyncRepo.autosync = false;
    paramSyncRepo.autosyncContent = false;
    paramSyncRepo.currentState = "Disable_sincing";

    int enum_indexF = mo.indexOfEnumerator("STATE_FILE_AND_DIR");
    metaEnumStateF = mo.enumerator(enum_indexF);

    QObject::connect(this, &IRepository::startGetContentFile, this, &IRepository::OnStartGetContentFile, Qt::DirectConnection);
    QObject::connect(this, &IRepository::endGetContentFile, this, &IRepository::OnEndGetContentFile, Qt::DirectConnection);
    QObject::connect(this, &IRepository::startDropContentFile, this, &IRepository::OnStartDropContentFile, Qt::DirectConnection);
    QObject::connect(this, &IRepository::endDropContentFile, this, &IRepository::OnEndDropContentFile, Qt::DirectConnection);

    dir.setPath("");
}
//----------------------------------------------------------------------------------------/
void IRepository::SetState(const STATE_REPOSITORY& state)
{
    QByteArray str = metaEnumState.valueToKey(int(state));
    paramSyncRepo.currentState = QString(str);
}
//----------------------------------------------------------------------------------------/
QString IRepository::GetState() const
{
    return paramSyncRepo.currentState;
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
    paramSyncRepo.autosync = autosync;
    paramSyncRepo.autosyncContent = autosyncContent;
}
//----------------------------------------------------------------------------------------/
void IRepository::UpdateParamSyncFileDirFull(const QString& curDir)
{
    // проверка на то, что текущий путь явлеяться поддиректорией корневого
    std::cout<<"New Dir = "<<curDir.toStdString().c_str()<<std::endl;
    std::cout<<"Local URL Dir = "<<localURL.toStdString().c_str()<<std::endl;

    assert(curDir.length() >= localURL.length() && curDir.contains(localURL, Qt::CaseSensitive));
    dir.setPath(curDir);

    paramSyncFileDir.clear();
    QStringList nameAllFilesAndDir = dir.entryList();
    QFileInfoList infoList = dir.entryInfoList();
    auto iteratorInfo = infoList.begin();
    for(auto iterator = nameAllFilesAndDir.begin(); iterator !=  nameAllFilesAndDir.end(); ++iterator, ++iteratorInfo)
    {
        if(*iterator == "." || *iterator == "..") continue;
        PARAMETR_FILEFOLDER_GIT_ANNEX paramTemp;
        paramTemp.autosync = true;
        {
            // текущее состояние
            QByteArray curState;
            if(IsGettingContentFileDir(*iterator) || IsDroppingContentFileDir(*iterator)){
                curState = metaEnumStateF.valueToKey(SyncingF);
            }
            else {
                curState = metaEnumStateF.valueToKey(SyncedF);
            }
            paramTemp.currentState = QString(curState);
        }
        paramTemp.fileInfo = *iteratorInfo;
        paramSyncFileDir[*iterator] = paramTemp;
    }
}
//----------------------------------------------------------------------------------------/
void IRepository::UpdateParamSyncFileDir()
{
    for(auto iterator = paramSyncFileDir.begin(); iterator !=  paramSyncFileDir.end(); ++iterator)
    {
        const QString fileName = iterator.key();
        PARAMETR_FILEFOLDER_GIT_ANNEX& paramSync = iterator.value();
        // текущее состояние
        QByteArray curState;
        if(IsGettingContentFileDir(fileName) || IsDroppingContentFileDir(fileName))
        {
            curState = metaEnumStateF.valueToKey(SyncingF);
            paramSync.currentState = QString(curState);
        }
        else
        {
            curState = metaEnumStateF.valueToKey(SyncedF);
            paramSync.currentState = QString(curState);
        }
    }
}
//----------------------------------------------------------------------------------------/
bool IRepository::IsGettingContentFileDir(const QString& file)
{
    for(auto iterator = gettingContentFile.constBegin(); iterator != gettingContentFile.constEnd(); ++iterator)
    {       
#if 0
        const QString gettingFile = *iterator;
        QString fullPathFile = dir.path() + "/" + file;
        // из fullPath нужно убрать ту часть, которая содержит localURL
        const QString relativePath = fullPathFile.replace(localURL +"/", "");
        std::cout<<"GettingFile = "<<gettingFile.toStdString().c_str()<<std::endl;
        std::cout<<"Full Path = "<<fullPathFile.toStdString().c_str()<<std::endl;
        std::cout<<"Relative Path = "<<relativePath.toStdString().c_str()<<std::endl;
#endif
        const QString relativePath = QString(dir.path() + "/" + file).replace(localURL +"/", "");
        if(DirContainsFile(*iterator, relativePath))
            return true;
    }
    return false;
}
//----------------------------------------------------------------------------------------/
bool IRepository::IsDroppingContentFileDir(const QString& file)
{
    for(auto iterator = droppingContentFile.constBegin(); iterator != droppingContentFile.constEnd(); ++iterator)
    {
        const QString relativePath = QString(dir.path() + "/" + file).replace(localURL +"/", "");
        if(DirContainsFile(*iterator, relativePath))
            return true;
    }
    return false;
}
//----------------------------------------------------------------------------------------/
bool IRepository::DirContainsFile(const QString& dir, const QString& file) const
{
    return dir.contains(file, Qt::CaseSensitive);
}
//----------------------------------------------------------------------------------------/
//    СЛУЖЕБНЫЕ СЛОТЫ
//----------------------------------------------------------------------------------------/
void IRepository::OnStartGetContentFile(const QString& file)
{
    if(std::find(gettingContentFile.begin(), gettingContentFile.end(), file) == gettingContentFile.end()){
        gettingContentFile.push_back(file);
    }
}
//----------------------------------------------------------------------------------------/
void IRepository::OnEndGetContentFile(const QString& file)
{
    auto itErase = std::find(gettingContentFile.begin(), gettingContentFile.end(), file);
    if(itErase != gettingContentFile.end()) {
        gettingContentFile.erase(itErase);
    }
    else
    {
        std::cout<<"WARNING!!!! В списке получаемых в текущий момент файлов нет файла, получение контента которого закончилось!!!"<<std::endl;
        #ifdef DEBUG
                assert(0);
        #endif
    }
}
//----------------------------------------------------------------------------------------/
void IRepository::OnStartDropContentFile(const QString& file)
{
    if(std::find(droppingContentFile.begin(), droppingContentFile.end(), file) == droppingContentFile.end()){
        droppingContentFile.push_back(file);
    }
}
//----------------------------------------------------------------------------------------/
void IRepository::OnEndDropContentFile(const QString& file)
{
    auto itErase = std::find(droppingContentFile.begin(), droppingContentFile.end(), file);
    if(itErase != droppingContentFile.end()) {
        droppingContentFile.erase(itErase);
    }
    else
    {
        std::cout<<"WARNING!!!! В списке удаляемых в текущий момент файлов нет файла, удаление контента которого закончилось!!!"<<std::endl;
        #ifdef DEBUG
                assert(0);
        #endif
    }
}
//----------------------------------------------------------------------------------------/
