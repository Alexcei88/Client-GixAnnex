#ifndef MODEL_ICONS_H
#define MODEL_ICONS_H

#include <QMap>
#include <QObject>

namespace GANN_MVC
{
class ControllerIcons;

class ModelQmlAndCIcons: public QObject
{
    Q_OBJECT
public:
    ModelQmlAndCIcons(ControllerIcons* contrIcons);
    ~ModelQmlAndCIcons();

    void            UpdateFileSyncIcons();

private:
    ControllerIcons* contrIcons;
    bool            exitThread;
};

}

#endif // MODEL_ICONS_H
