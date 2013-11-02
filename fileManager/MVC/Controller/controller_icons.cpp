#include "controller_icons.h"
#include "../../resourcegenerator.h"

// Qt stuff
#include <QFileInfo>
#include <QMimeDatabase>
#include <QMimeType>
#include <QIcon>
#include <QThread>

#include <assert.h>
#include <iostream>


using namespace GANN_MVC;
//----------------------------------------------------------------------------------------/
ControllerIcons::ControllerIcons() :
    mainModel(QSharedPointer<ModelQmlAndCRepository>(new ModelQmlAndCRepository()))
  , modelIcons(QSharedPointer<ModelQmlAndCIcons>(new ModelQmlAndCIcons(this)))
  , thread(0l)
{
    QObject::connect(this, &ControllerIcons::changedParentDIrectory, this, &ControllerIcons::OnChangeParrentDirectory);
}
ControllerIcons::~ControllerIcons()
{
    // посылаем сигнал о завершении потока обновлении иконок синхронизации
    if(thread != 0 && thread->isRunning())
    {
        emit stopThread();
        while(thread->isFinished());
    }
}
//----------------------------------------------------------------------------------------/
QVariant ControllerIcons::GetPathIconsFile(QVariant file) const
{    
    static QMimeDatabase dataBase;
    QFileInfo fileInfo(file.toString());
    QMimeType type = dataBase.mimeTypeForFile(fileInfo);
#if 0
    QString pathIcons;
    if(QIcon::hasThemeIcon(type.iconName()))
    {
        pathIcons = "qrc:/mimetypes/resource/mimetypes/" + type.iconName() + ".png";
    }
    else
    {
        // определяем другой общий для этот типа
        pathIcons = "qrc:/mimetypes/resource/mimetypes/" + type.genericIconName() + ".png";
    }
#else
    QString pathIcons = ResourceGenerator::getInstance()->GetResourcePath(type);
#endif
    return QVariant(pathIcons);
}
//----------------------------------------------------------------------------------------/
QVariant ControllerIcons::GetLastModifiedFile(QVariant file) const
{
    return mainModel->GetLastModifiedFile(file.toString());
}
//----------------------------------------------------------------------------------------/
QVariant ControllerIcons::GetSizeFile(QVariant file) const
{
    return mainModel->GetSizeFile(file.toString());
}
//----------------------------------------------------------------------------------------/
void ControllerIcons::StartThreadIconsSync()
{
    if(thread != 0 && thread->isRunning())
        return;

    // запускаем поток обновления иконок синхронизации
    thread = new QThread(this);
    modelIcons->moveToThread(thread);
    QObject::connect(thread, &QThread::started, [=] {modelIcons->UpdateFileSyncIcons(); });
    QObject::connect(this, SIGNAL(stopThread()), thread, SLOT(quit()));
    thread->start();
}
//----------------------------------------------------------------------------------------/
void ControllerIcons::OnChangeParrentDirectory(QString curDir)
{
    assert(dir.exists(curDir));
    // посылаем модели о смене текущей директории отображения в текущем репозитории
    mainModel->ChangeCurrentViewDirectory(curDir);

    dir.setPath(curDir);

    // обновляем полностю список состояния иконок синхронизации
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
        if(*iterator == "." || *iterator == "..") continue;
        IRepository::PARAMETR_FILEFOLDER_GIT_ANNEX paramSyncCur = paramSync[*iterator];
        stateIconsFileSync[*iterator] = paramSyncCur.currentState;
    }
}
//----------------------------------------------------------------------------------------/


