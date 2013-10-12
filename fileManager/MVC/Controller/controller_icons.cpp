#include "controller_icons.h"

#include <QString>
#include <iostream>
#include <QFileInfo>
#include <QMimeDatabase>
#include <QMimeType>

using namespace GANN_MVC;
//----------------------------------------------------------------------------------------/
ControllerIcons::ControllerIcons()
{}
//----------------------------------------------------------------------------------------/
QVariant ControllerIcons::GetPathIconsFile(QVariant file) const
{
    QFileInfo fileInfo(file.toString());
    QMimeType type = QMimeDatabase().mimeTypeForFile(fileInfo);
    const QString pathIcons = "qrc:/mimetypes/resource/mimetypes/" + type.iconName() + ".png";
    return QVariant(pathIcons);

}
//----------------------------------------------------------------------------------------/

