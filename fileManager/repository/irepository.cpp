#include "irepository.h"

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
}
//----------------------------------------------------------------------------------------/
