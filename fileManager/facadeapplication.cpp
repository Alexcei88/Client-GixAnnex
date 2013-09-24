#include "facadeapplication.h"

boost::shared_ptr<FacadeApplication> FacadeApplication::instance = boost::shared_ptr<FacadeApplication>();
//----------------------------------------------------------------------------------------/
FacadeApplication::FacadeApplication() :
//    pathFileRepoConfig("qrc:/config/config_repo")
  pathFileRepoConfig("ganx-repository.xml")
{
    fileRepoConfig.setFileName(pathFileRepoConfig);
}
//----------------------------------------------------------------------------------------/
FacadeApplication* FacadeApplication::getInstance()
{
    if(instance.get() == 0)
        instance = boost::shared_ptr<FacadeApplication>(new FacadeApplication());
    return instance.get();
}
//----------------------------------------------------------------------------------------/
void FacadeApplication::SaveRepository(const QString& localURL, const QString& remoteURL, const QString& nameRepo)
{
    QDomDocument doc;

    if(!fileRepoConfig.open(QIODevice::ReadOnly))
    {
        printf("ERROR: Unable to open file. Repository was not save!!!");
        return;
    }
    if(!doc.setContent(&fileRepoConfig))
    {
        printf("ERROR: file parsing error!!!");
        return;
    }
    // ожержимое тега зарегистрированных репозитория
    QDomElement listRepo;

}
//----------------------------------------------------------------------------------------/
