#include "facadeapplication.h"
#include "MVC/Controller/controller_repository.h"
#include "MVC/Controller/controller_icons.h"
#include "repository/trepository.h"
#include "resourcegenerator.h"
#include <qml/components/message_box//qmlmessage.h>
#include <qml/components/folder_model/folderlistmodel.h>

#include <QQmlEngine>
#include <QQmlComponent>
#include <QTextStream>
#include <QThreadPool>


using namespace GANN_DEFINE;

FacadeApplication* FacadeApplication::instance = 0;
//----------------------------------------------------------------------------------------/
FacadeApplication::FacadeApplication() :
    QObject()
  , pathFileRepoConfig("ganx-repository.xml")
  , currentRepository(repository.end())
  , systemTray(0l)
//    pathFileRepoConfig(":/config/config_repo")
{
    fileRepoConfig.setFileName(pathFileRepoConfig);

    // генерируем список путей до иконок
    ResourceGenerator::getInstance();

    // разрешаем выполнять задачу git-annex только в одном потоке
    // больше 1 процесса git-annex создать все равно не даст
    QThreadPool::globalInstance()->setMaxThreadCount(1);

    // загружаем из конфигов существующие репозитории
    LoadRepositories();

    // запускаем демон за просмотром директорий с репозиториями
    WatchRepositories();

    // инициализируем связь C и QML
    InitClassCAndQML();

    // запускаем таймер синхронизации данных
    QObject::connect(&timeSync, &QTimer::timeout, [=](){this->TimeOutTimeSync();});
    // интервал срабатывания тайминга(в миллисек)
    const int timeInterval = 20000;
    timeSync.setInterval(timeInterval);
    timeSync.start();
}
//----------------------------------------------------------------------------------------/
FacadeApplication* FacadeApplication::getInstance()
{
    if(instance == 0)
        instance = new FacadeApplication();
    return instance;
}
//----------------------------------------------------------------------------------------/
void FacadeApplication::RemoveInstance()
{
    delete instance;
}
//----------------------------------------------------------------------------------------/
FacadeApplication::~FacadeApplication()
{
    // выключаем таймер синхронизации данных
    timeSync.stop();

    // останавливаем поток синхронизации иконок
    emit stopThreadIconsSync();

#warning NOT_WORK
    // все остальные задачи нужно убивать к чертовой матери, и останавливать демоны
    // ждем секунду, чтобы QThreadPool уничтожил все свои потоки
    QThreadPool::globalInstance()->setExpiryTimeout(1000);
    QThreadPool::globalInstance()->waitForDone(1000);

    // останавливаем демон просмотра за директориями репозитория
    WatchRepositories(false);
    // ждем, пока демоны выключаться
    QThreadPool::globalInstance()->waitForDone();

    ResourceGenerator::RemoveInstance();
}
//----------------------------------------------------------------------------------------/
void FacadeApplication::LoadRepositories()
{
    // проверка есть ли нужный нам файл в домашнем каталоге(если нет, то создаем пустой)
#warning MUST_DO

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
void FacadeApplication::SaveRepository(const QString& localURL, const QString& remoteURL, const QString& nameRepo,
                                       const bool autosync, const bool autosyncContent
                                       )
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
    // cодержимое тега зарегистрированных репозиториев
    // создаем элемент репо
    QDomElement newRepo = doc.createElement("repo");

    // создаем атрибуты элемента
    {
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
    }

    // создаем дочерний элемент у элемента newRepo элемент paramSync
    QDomElement paramSync = doc.createElement("paramSync");

    // создаем аттрибуты элемента
    {
        QDomAttr attrParamAutoSync = doc.createAttribute("autosync");
        attrParamAutoSync.setValue(QString::number(int(autosync)));
        paramSync.setAttributeNode(attrParamAutoSync);

        QDomAttr attrParamAutoSyncContent = doc.createAttribute("autosyncContent");
        attrParamAutoSyncContent.setValue(QString::number(int(autosyncContent)));
        paramSync.setAttributeNode(attrParamAutoSyncContent);
    }
    // теперь устанавливаем этот элемент как дочерний к элементу newRepo
    newRepo.appendChild(paramSync);

    fileRepoConfig.reset();
    QTextStream(&fileRepoConfig) << doc.toString();
    fileRepoConfig.close();
}
//----------------------------------------------------------------------------------------/
void FacadeApplication::WatchRepositories(const bool start) const
{
    for(auto itRepo = repository.begin(); itRepo != repository.end(); ++itRepo)
    {
        WatchRepository(itRepo->second.get(), start);
    }
}
//----------------------------------------------------------------------------------------/
void FacadeApplication::WatchRepository(const IRepository* repository, const bool start) const
{
    start ? repository->StartWatchRepository() : repository->StopWatchRepository();
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

        // запускаем демон просмотра за каталогом с репозиторием
        WatchRepository(repository[localURL].get());
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
        // текущий репозиторий мы уже синхронизировали выше
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
    qmlRegisterType<QMLMessage>("Message", 1, 0, "MessageBox");
    qmlRegisterType<QMLFolderListModel>("FolderListModel", 1, 0, "NewFolderListModel");
}
//----------------------------------------------------------------------------------------/
