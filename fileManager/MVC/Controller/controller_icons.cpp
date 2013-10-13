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
ControllerIcons::ControllerIcons()
{
    stateIconsFileSync.reserve(10);
    stateIconsFileSync.push_back("syncing");
    stateIconsFileSync.push_back("syncing");
    stateIconsFileSync.push_back("synced");
    stateIconsFileSync.push_back("synced");
    stateIconsFileSync.push_back("synced");
    stateIconsFileSync.push_back("syncing");
    stateIconsFileSync.push_back("syncing");
    stateIconsFileSync.push_back("syncing");
    stateIconsFileSync.push_back("syncing");
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
    std::cout<<"curDir = "<<curDir.toStdString().c_str()<<std::endl;
}
//----------------------------------------------------------------------------------------/


