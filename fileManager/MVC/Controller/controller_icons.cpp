#include "controller_icons.h"

// Qt stuff
#include <QString>
#include <iostream>
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
{
    QObject::connect(this, &ControllerIcons::changedParentDIrectory, this, &ControllerIcons::OnChangeParrentDirectory);

    // запускаем поток обновления иконок синхронизации
    QThread* thread = new QThread(this);
    modelIcons->moveToThread(thread);
    QObject::connect(thread, &QThread::started, [=] {modelIcons->UpdateFileSyncIcons(); });
    QObject::connect(this, SIGNAL(stopThread()), thread, SLOT(quit()));
    thread->start();
}
ControllerIcons::~ControllerIcons()
{
    // посылаем сигнал о завершении потока обнолвении иконок синхронизации
    emit stopThread();
}
//----------------------------------------------------------------------------------------/
QVariant ControllerIcons::GetPathIconsFile(QVariant file) const
{
    QFileInfo fileInfo(file.toString());
    QMimeType type = QMimeDatabase().mimeTypeForFile(fileInfo);
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
    return QVariant(pathIcons);
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


