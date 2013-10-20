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

    QObject::connect(this, &IRepository::startGetContentFile, this, &IRepository::OnStartGetContentFile);
    QObject::connect(this, &IRepository::endGetContentFile, this, &IRepository::OnEndGetContentFile);
}
//----------------------------------------------------------------------------------------/
void IRepository::SetState(const STATE_REPOSITORY& state)
{
    std::cout<<"State = "<<int(state)<<std::endl;
    QByteArray str = metaEnumState.valueToKey(int(state));
    std::cout<<"State = "<<QString(state).toStdString().c_str()<<std::endl;
    paramSyncRepo.currentState = QString(state);
}
//----------------------------------------------------------------------------------------/
QString IRepository::GetState() const
{
    return paramSyncRepo.currentState;
}
//----------------------------------------------------------------------------------------/
void IRepository::SetStateFileDir(const QString& fileDirName, const STATE_REPOSITORY& state)
{

}
//----------------------------------------------------------------------------------------/
QString IRepository::GetStateFileDir(const QString& fileDirName) const
{

}
//----------------------------------------------------------------------------------------/
void IRepository::SetParamSyncRepository(const bool& autosync, const bool& autosyncContent)
{
    paramSyncRepo.autosync = autosync;
    paramSyncRepo.autosyncContent = autosyncContent;
}
//----------------------------------------------------------------------------------------/
void IRepository::UpdateParamSyncFileDir(const QString& curDir)
{
    // проверка на то, что текущий путь явлеяться поддиректорией корневого
    std::cout<<"New Dir = "<<curDir.toStdString().c_str()<<std::endl;
    std::cout<<"Local URL Dir = "<<localURL.toStdString().c_str()<<std::endl;

    assert(curDir.length() >= localURL.length() && curDir.contains(localURL, Qt::CaseSensitive));
    dir.setPath(curDir);

    paramSyncFileDir.clear();
    QStringList nameAllFilesAndDir = dir.entryList();
    for(auto iterator = nameAllFilesAndDir.begin(); iterator !=  nameAllFilesAndDir.end(); ++iterator)
    {
        if(*iterator == "." || *iterator == "..") continue;
        PARAMETR_FILEFOLDER_GIT_ANNEX paramTemp;
        paramTemp.autosync = true;
        QByteArray curState = metaEnumStateF.valueToKey(SyncedF);
        paramTemp.currentState = QString(curState);
        paramSyncFileDir[*iterator] = paramTemp;
    }
}
//----------------------------------------------------------------------------------------/
//    СЛУЖЕБНЫЕ СЛОТЫ
//----------------------------------------------------------------------------------------/
void IRepository::OnStartGetContentFile(const QString& file)
{

}
//----------------------------------------------------------------------------------------/
void IRepository::OnEndGetContentFile(const QString& file)
{

}
//----------------------------------------------------------------------------------------/
