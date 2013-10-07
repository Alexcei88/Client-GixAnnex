#include "facadeapplication.h"
#include "MVC/Controller/controller_repository.h"
#include "repository/trepository.h"
#include "resourcegenerator.h"

#include <QQmlEngine>
#include <QQmlComponent>
#include <QTextStream>
#include <QThreadPool>


using namespace GANN_DEFINE;

boost::shared_ptr<FacadeApplication> FacadeApplication::instance = boost::shared_ptr<FacadeApplication>();
//----------------------------------------------------------------------------------------/
FacadeApplication::FacadeApplication() :
    pathFileRepoConfig("ganx-repository.xml")
  , currentRepository(repository.end())
//    pathFileRepoConfig(":/config/config_repo")
{
    fileRepoConfig.setFileName(pathFileRepoConfig);

    // загружаем ресурсные файлы
    ResourceGenerator::getInstance();

    // загружаем из конфигов репозитории
    LoadRepositories();

    // инициализируем связь C и QML
    InitClassCAndQML();

    // разрешаем выполнять задачу только в одном потоке
    // больше 1 процесса git-annex создать все равно нельзя
    QThreadPool::globalInstance()->setMaxThreadCount(1);

    // делаем таймер, и запускаем его
    QObject::connect(&timeSync, &QTimer::timeout, [=](){this->TimeOutTimeSync();});
    // интервал срабатывания тайминга(в миллисек)
    const int timeInterval = 30000;
    timeSync.setInterval(30000);
    timeSync.start();
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

        std::unique_ptr<IRepository> tempRepo(new TRepository(localUrl, remoteUrl, nameRepo));

        // читаем список параметров автосинхронизации
        {
            QDomNodeList nodeSync = listRepo.at(countRepo).childNodes();
            assert(nodeSync.size() == 1);
            QDomNamedNodeMap nodeSyncMap = nodeSync.at(0).attributes();
            assert(nodeSyncMap.count() == 2);

            QDomAttr attrSyncRepo = nodeSyncMap.namedItem("autosync").toAttr();
            const bool autosync = attrSyncRepo.value().toInt();
            QDomAttr attrSyncRepoContent = nodeSyncMap.namedItem("autosyncContent").toAttr();
            const bool autosyncContent = attrSyncRepoContent.value().toInt();
            tempRepo->SetParamSyncRepository(autosync, autosyncContent);
            autosync ? tempRepo->SetState(IRepository::Synced) : tempRepo->SetState(IRepository::Disable_sinc);
        }

        repository[localUrl] = std::move(tempRepo);
        if(countRepo == 0)
            currentRepository = repository.begin();
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
        std::unique_ptr<IRepository> tempRepo(newRepo);
        repository[localURL] = std::move(tempRepo);
    }
    return result;
}
//----------------------------------------------------------------------------------------/
void FacadeApplication::ChangeCurrentRepository(const QString& dir)
{
    if(!repository.empty())
    {
        auto iterator = repository.find(dir);
        assert(iterator != repository.end());
        currentRepository = iterator;
    }
}
//----------------------------------------------------------------------------------------/
void FacadeApplication::TimeOutTimeSync()
{
    timeSync.stop();
    // идем по все репозиториям, и выполняем синхронизацию
    std::cout<<"Timer Signal End"<<std::endl;
    if(currentRepository != repository.end())
    {
        // выполняем синхронизацию активного репозитория
        IRepository *repository = currentRepository->second.get();
        if(repository->GetParamSyncRepository())
            repository->SyncRepository();
        // синхронизацию контента
        if(repository->GetParamSyncContentRepository())
            repository->GetContentFile(".");
    }
    // теперь всех остальных
    for(auto iterator = repository.begin(); iterator != repository.end(); ++iterator)
    {
        // текущий репозитирой мы уже синхронизировали
        if(iterator != currentRepository)
        {
            // выполняем синхронизацию активного репозитория
            IRepository *repository = iterator->second.get();
            if(repository->GetParamSyncRepository())
                repository->SyncRepository();
            if(repository->GetParamSyncContentRepository())
                repository->GetContentFile(".");
        }
    }
    timeSync.start();
}
//----------------------------------------------------------------------------------------/
void FacadeApplication::InitClassCAndQML()
{
    qmlRegisterType<GANN_MVC::ControllerRepository>("Repository", 1, 0, "ControllerRepository");
}
//----------------------------------------------------------------------------------------/
