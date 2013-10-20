#include "controller_icons.h"

#include <QString>
#include <iostream>
#include <QFileInfo>
#include <QMimeDatabase>
#include <QMimeType>
#include <QIcon>

#include <assert.h>
#include <iostream>

using namespace GANN_MVC;
//----------------------------------------------------------------------------------------/
ControllerIcons::ControllerIcons() :
    model(QSharedPointer<ModelQmlAndCRepository>(new ModelQmlAndCRepository()))
{
    QObject::connect(this, &ControllerIcons::changedParentDIrectory, this, &ControllerIcons::OnChangeParrentDirectory);
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
    model->ChangeCurrentViewDirectory(curDir);

    dir.setPath(curDir);

    // обновляем полностю список состояния иконок синхронизации
    UpdateStateIconsFileSync();
}
//----------------------------------------------------------------------------------------/
void ControllerIcons::UpdateStateIconsFileSync()
{
    // получить мэп состояний
    const QMap<QString, IRepository::PARAMETR_FILEFOLDER_GIT_ANNEX>& paramSync = model->GetParamSyncFileDir();
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
