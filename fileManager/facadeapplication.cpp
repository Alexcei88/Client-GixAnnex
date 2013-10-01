#include "facadeapplication.h"
#include "MVC/Controller/controller_repository.h"
#include "repository/trepository.h"

#include <QQmlEngine>
#include <QQmlComponent>
#include <QTextStream>

using namespace GANN_DEFINE;

boost::shared_ptr<FacadeApplication> FacadeApplication::instance = boost::shared_ptr<FacadeApplication>();
//----------------------------------------------------------------------------------------/
FacadeApplication::FacadeApplication() :
    pathFileRepoConfig("ganx-repository.xml")
//    pathFileRepoConfig(":/config/config_repo")
{
    fileRepoConfig.setFileName(pathFileRepoConfig);
    // инициализируем связь C и QML
    InitClassCAndQML();

    // загружаем из конфигов репозитории
    LoadRepositories();    
}
//----------------------------------------------------------------------------------------/
FacadeApplication* FacadeApplication::getInstance()
{
    if(instance.get() == 0)
        instance = boost::shared_ptr<FacadeApplication>(new FacadeApplication());
    return instance.get();
}
//----------------------------------------------------------------------------------------/
void FacadeApplication::LoadRepositories()
{
    QDomDocument doc;
    if(!fileRepoConfig.open(QIODevice::ReadOnly))
    {
        printf("ERROR: Unable to open file. Repositories was not load!!!");
        return;
    }
    if(!doc.setContent(&fileRepoConfig))
    {
        printf("ERROR: file parsing error!!!");
        fileRepoConfig.close();
        return;
    }

    QDomElement elRepoRegistry = doc.firstChildElement("reporegistry");
    QDomNodeList listRepo = elRepoRegistry.elementsByTagName("repo");
    for(int countRepo = 0; countRepo < listRepo.size(); ++countRepo)
    {
        // парсим и заполняем вектор репозиториев
        QDomNamedNodeMap nodeMap = listRepo.at(countRepo).attributes();
        assert(nodeMap.count() == 3);

        QDomAttr attrLocalUrl = nodeMap.namedItem("localUrl").toAttr();
        const QString localUrl = attrLocalUrl.value();

        QDomAttr attrRemoteUrl = nodeMap.namedItem("remoteUrl").toAttr();
        const QString remoteUrl = attrRemoteUrl.value();

        QDomAttr attrNameRepo = nodeMap.namedItem("nameRepo").toAttr();
        const QString nameRepo = attrNameRepo.value();

        boost::shared_ptr<IRepository> tempRepo(new TRepository(localUrl, remoteUrl, nameRepo));
        repository[localUrl] = tempRepo;
    }
    fileRepoConfig.close();
}
//----------------------------------------------------------------------------------------/
void FacadeApplication::SaveRepository(const QString& localURL, const QString& remoteURL, const QString& nameRepo)
{
    QDomDocument doc;

    if(!fileRepoConfig.open(QIODevice::ReadWrite))
    {
        std::cout<<fileRepoConfig.errorString().toStdString().c_str()<<std::endl;
        printf("ERROR: Unable to open file. Repository was not save!!!");
        return;
    }
    if(!doc.setContent(&fileRepoConfig))
    {
        printf("ERROR: file parsing error!!!");
        fileRepoConfig.close();
        return;
    }
    // cодержимое тега зарегистрированных репозитория
    // создаем элемент
    QDomElement newRepo = doc.createElement("repo");

    // создаем атрибуты элемента
    QDomAttr attrNewRepo = doc.createAttribute("localUrl");
    attrNewRepo.setValue(localURL);
    newRepo.setAttributeNode(attrNewRepo);

    QDomAttr attrNewRepo_1 = doc.createAttribute("remoteUrl");
    attrNewRepo_1.setValue(remoteURL);
    newRepo.setAttributeNode(attrNewRepo_1);

    QDomAttr attrNewRepo_2 = doc.createAttribute("nameRepo");
    attrNewRepo_2.setValue(nameRepo);
    newRepo.setAttributeNode(attrNewRepo_2);

    QDomElement elReporegistry = doc.firstChildElement("reporegistry");
    elReporegistry.appendChild(newRepo);

    fileRepoConfig.reset();
    QTextStream(&fileRepoConfig) << doc.toString();
    fileRepoConfig.close();

}
//----------------------------------------------------------------------------------------/
GANN_DEFINE::RESULT_EXEC_PROCESS FacadeApplication::StartCloneRepository(QString &localURL, const QString &remoteURL, const QString &nameRepo)
{
    TRepository* newRepo = new TRepository;
    RESULT_EXEC_PROCESS result = newRepo->CloneRepository(localURL, nameRepo, remoteURL);
    if(result == NO_ERROR)
    {
        boost::shared_ptr<IRepository> tempRepo(newRepo);
        repository[localURL] = tempRepo;
    }
    return result;
}
//----------------------------------------------------------------------------------------/
void FacadeApplication::CancelCloneRepository(const bool breakCommand)
{
    systemTray->CancelCloneRepository();
}
//----------------------------------------------------------------------------------------/
bool FacadeApplication::ReLoadListRepository() const
{
    return systemTray->ReLoadListRepository();
}
//----------------------------------------------------------------------------------------/
void FacadeApplication::ChangeCurrentRepository(const QString& dir)
{

}
//----------------------------------------------------------------------------------------/
void FacadeApplication::InitClassCAndQML()
{
    qmlRegisterType<GANN_MVC::ControllerRepository>("Repository", 1, 0, "ControllerRepository");
}
//----------------------------------------------------------------------------------------/
