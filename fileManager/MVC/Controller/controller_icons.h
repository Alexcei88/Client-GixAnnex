#ifndef CONTROLLER_ICONS_H
#define CONTROLLER_ICONS_H

/*
 * Класс КОНТРОЛЛЕР ИКОНОК, задача которого генерация путей дя загрузки нужных иконок в QML
 * например, в зависимости от MimeType будет разные иконки грузиться
*/

#include <QObject>
#include <QVariant>

namespace GANN_MVC
{

class ControllerIcons : public QObject
{
    Q_OBJECT
public:
    ControllerIcons();

    /** @brief возврашает путь иконки в зависимости от mimetype файла */
    Q_INVOKABLE QVariant GetPathIconsFile(QVariant file) const;

private:
};

}
#endif // CONTROLLER_ICONS_H
