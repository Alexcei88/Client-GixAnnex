#include "controller_icons.h"
#include "../../resourcegenerator.h"
#include "../../facadeapplication.h"

// Qt stuff
#include <QFileInfo>
#include <QMimeDatabase>
#include <QMimeType>
#include <QIcon>
#include <QThread>

#include <assert.h>
#include <iostream>

using namespace GANN_MVC;

QThread* ControllerIcons::thread = 0l;
//----------------------------------------------------------------------------------------/
ControllerIcons::ControllerIcons() :
    mainModel(QSharedPointer<ModelQmlAndCRepository>(new ModelQmlAndCRepository()))
  , modelIcons(new ModelQmlAndCIcons(this))
{
    QObject::connect(this, &ControllerIcons::changedParentDirectory, this, &ControllerIcons::OnChangeParentDirectory);
    dir.setFilter(QDir::NoDotAndDotDot | QDir::Files | QDir::AllDirs | QDir::System);
}
ControllerIcons::~ControllerIcons()
{
    delete modelIcons;
    modelIcons = 0;
}
//----------------------------------------------------------------------------------------/
QVariant ControllerIcons::getPathIconsFileDirectoryView(QUrl file) const
{    
    static const QMimeDatabase dataBase;
    const QFileInfo fileInfo(file.toLocalFile());
    const QMimeType type = dataBase.mimeTypeForFile(fileInfo);
    const QString pathIcons = ResourceGenerator::getInstance()->GetResourcePathDirectoryView(type);
    return QVariant(pathIcons);
}
//----------------------------------------------------------------------------------------/
QVariant ControllerIcons::getPathIconsFilePropertyFile(QUrl file) const
{    
    static const QMimeDatabase dataBase;
    const QFileInfo fileInfo(file.toLocalFile());
    const QMimeType type = dataBase.mimeTypeForFile(fileInfo);
    const QString pathIcons = ResourceGenerator::getInstance()->GetResourcePathPropertyFile(type);
    return QVariant(pathIcons);
}
//----------------------------------------------------------------------------------------/
QVariant ControllerIcons::getLastModifiedFile(QUrl file) const
{
    return mainModel->GetLastModifiedFile(file.toLocalFile());
}
//----------------------------------------------------------------------------------------/
QVariant ControllerIcons::getSizeFile(QUrl file) const
{
    return mainModel->GetSizeFile(file.toLocalFile());
}
//----------------------------------------------------------------------------------------/
void ControllerIcons::startThreadIconsSync()
{
    if(thread != 0 && thread->isRunning())
        return;

    // запускаем поток обновления иконок синхронизации
    thread = new QThread();
    modelIcons->moveToThread(thread);
    QObject::connect(thread, &QThread::started, [=] {modelIcons->UpdateFileSyncIcons(); });

    FacadeApplication* facade = FacadeApplication::getInstance();
    QObject::connect(facade, &FacadeApplication::stopThreadIconsSync, [=] { ControllerIcons::StopThreadIconsSync(); });
    thread->start();
}
//----------------------------------------------------------------------------------------/
void ControllerIcons::StopThreadIconsSync()
{
    if(thread)
    {
        if(thread->isRunning())
        {
            thread->quit();
            thread->wait();
        }
        delete thread;
        thread = 0;
    }
}
//----------------------------------------------------------------------------------------/
void ControllerIcons::OnChangeParentDirectory(QUrl curDir)
{
    if(curDir.isEmpty())
        return;

    assert(dir.exists(curDir.toLocalFile()));

    QMutex& mutex = FacadeApplication::threadModel.mutexSyncIcons;
    QMutexLocker mutexLocker(&mutex);

    static int number = 0;
    std::cout<<number++<<"Change Parent Directory"<<curDir.toLocalFile().toStdString().c_str()<<std::endl;

    // посылаем модели сигнал о смене текущей директории отображения в текущем репозитории
    mainModel->ChangeCurrentViewDirectory(curDir.toLocalFile());

    dir.setPath(curDir.toLocalFile());

    // обновляем полностью список состояния иконок синхронизации
    UpdateStateIconsFileSync();
}
//----------------------------------------------------------------------------------------/
void ControllerIcons::UpdateStateIconsFileSync()
{
    // получить мэп состояний
    const QMap<QString, IRepository::PARAMETR_FILEFOLDER_GIT_ANNEX>& paramSync = mainModel->GetParamSyncFileDir();
    stateIconsFileSync.clear();
    QStringList nameAllFilesAndDir = dir.entryList();
    for(auto iterator = nameAllFilesAndDir.begin(); iterator !=  nameAllFilesAndDir.end(); ++iterator)
    {
        IRepository::PARAMETR_FILEFOLDER_GIT_ANNEX paramSyncCur = paramSync[*iterator];
        stateIconsFileSync[*iterator] = paramSyncCur.currentState;
    }
}
//----------------------------------------------------------------------------------------/


