#include "irepository.h"

//----------------------------------------------------------------------------------------/
IRepository::IRepository()
{
    InitClass();
    paramSyncRepo.autosync = false;
    paramSyncRepo.autosyncContent = false;
}
//----------------------------------------------------------------------------------------/
IRepository::IRepository(const QString& localUrl, const QString& remoteUrl, const QString& nameRepo):
   remoteURL(remoteUrl)
  ,localURL(localUrl)
  ,nameRepo(nameRepo)
{
    InitClass();
    paramSyncRepo.autosync = false;
    paramSyncRepo.autosyncContent = false;
}
//----------------------------------------------------------------------------------------/
void IRepository::InitClass()
{
    shellCommand = boost::make_shared<ShellCommand>();
}
//----------------------------------------------------------------------------------------/
void IRepository::SetParamSyncRepository(const bool& autosync, const bool& autosyncContent)
{
    paramSyncRepo.autosync = autosync;
    paramSyncRepo.autosyncContent = autosyncContent;
}
//----------------------------------------------------------------------------------------/

