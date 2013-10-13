#ifndef CONTROLLER_ICONS_H
#define CONTROLLER_ICONS_H

/*
 * Класс КОНТРОЛЛЕР ИКОНОК, задача которого генерация путей дя загрузки нужных иконок в QML
 * например, в зависимости от MimeType будет разные иконки грузиться
*/

#include <QObject>
#include <QVariant>
#include <QStringList>

namespace GANN_MVC
{

class ControllerIcons : public QObject
{
    Q_OBJECT
public:
    ControllerIcons();

    /** @brief текущий отображаемый путь */

    /** @brief вектор состояний иконок */
    Q_PROPERTY(QVariantList stateIconsFileSync READ GetStateIconsFileSync WRITE SetStateIconsFileSync NOTIFY stateIconsFileSyncChanged);

    void                SetStateIconsFileSync (QVariantList stateIcons) { stateIconsFileSync = stateIcons; };
    QVariantList        GetStateIconsFileSync() { return stateIconsFileSync; };

    /** @brief возвращает путь иконки в зависимости от mimetype файла
    @param file - путь к файлу */
    Q_INVOKABLE QVariant GetPathIconsFile(QVariant file) const;

public slots:
    void                OnChangeParrentDirectory(QString curDir);

private:
    /** @brief список текущего состояния иконок синхронизации
    * в зависимости от текущего списка отображаемых иконок файлов(директорий) */
    QVariantList        stateIconsFileSync;

signals:
    void                stateIconsFileSyncChanged(QVariantList);
};

}
#endif // CONTROLLER_ICONS_H
