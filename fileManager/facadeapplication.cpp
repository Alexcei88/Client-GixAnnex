#include "facadeapplication.h"
#include "MVC/Controller/controller_repository.h"
#include "MVC/Controller/controller_icons.h"
#include "repository/trepository.h"
#include "resourcegenerator.h"
#include <qml/components/error_message/qmlerrormessage.h>

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
  , systemTray(0l)
//    pathFileRepoConfig(":/config/config_repo")
{
    fileRepoConfig.setFileName(pathFileRepoConfig);

    // генерируем список путей до иконок
    ResourceGenerator::getInstance();

    // загружаем из конфигов существующие репозитории
    LoadRepositories();

    // инициализируем связь C и QML
    InitClassCAndQML();

    // разрешаем выполнять задачу git-annex только в одном потоке
    // больше 1 процесса git-annex создать все равно не даст
    QThreadPool::globalInstance()->setMaxThreadCount(1);

    // запускаем таймер синхронизации данных
    QObject::connect(&timeSync, &QTimer::timeout, [=](){this->TimeOutTimeSync();});
    // интервал срабатывания тайминга(в миллисек)
    const int timeInterval = 30000;
    timeSync.setInterval(timeInterval);
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
            autosync ? tempRepo->SetState(IRepository::Synced) : tempRepo->SetState(IRepository::Disable_sincing);
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
    static QDir dir;
    dir.setPath(localURL);
    if(!dir.exists())
    {
        // директория, куда будем копировать, не существует.
        return DIRECTORY_NOT_EXIST;
    }
    TRepository* newRepo = new TRepository;
    RESULT_EXEC_PROCESS result = newRepo->CloneRepository(localURL, nameRepo, remoteURL);
    if(result == NO_ERROR)
    {
        std::unique_ptr<IRepository> tempRepo(newRepo);
        repository[localURL] = std::move(tempRepo);
    }
    else
    {
        lastError = newRepo->GetLastError();
        delete newRepo;
        newRepo = 0l;
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
    qmlRegisterType<GANN_MVC::ControllerIcons>("Icons", 1, 0, "ControllerIcons");
    qmlRegisterType<QMLErrorMessage>("Error", 1, 0, "ErrorMessage");
}
//----------------------------------------------------------------------------------------/
