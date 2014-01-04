#ifndef MODEL_ICONS_H
#define MODEL_ICONS_H

#include <QMap>
#include <QObject>
#include "define.h"

class ThreadSyncIcons;

namespace GANN_MVC
{
class ControllerIcons;

class ModelQmlAndCIcons: public QObject
{
    Q_OBJECT
public:
    ModelQmlAndCIcons(ControllerIcons* contrIcons);
    ~ModelQmlAndCIcons();

    /** @brief  Запуск потока обновления иконок синхронизации */
    void            StartThreadIconsSync();

    /** @brief Остановка потока обновления иконок синхронизации */
    static void     StopThreadIconsSync();

private:
    ControllerIcons* contrIcons;
    boost::shared_ptr<ControllerIcons> threadSyncIcons;

    // поток, в котором будет обновление иконок синхронизации в представлении(один на все объекты)
    static QThread*   thread;
};

}

#endif // MODEL_ICONS_H
