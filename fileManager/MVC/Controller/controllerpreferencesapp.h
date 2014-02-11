#ifndef CONTROLLERPREFERENCESAPP_H
#define CONTROLLERPREFERENCESAPP_H

// Qt stuff
#include <QObject>
#include <QSharedPointer>

#include "../Model/model_preferencesapp.h"

namespace GANN_MVC
{
class ControllerPreferencesApp : public QObject
{
    Q_OBJECT

public:
    ControllerPreferencesApp();

    /** @brief Закрыть окно свойства приложения */
    Q_INVOKABLE void        closePreferencesAppView() const;

private:
    const QSharedPointer<ModelQmlAndCPreferencesApp>  model;

};
}

#endif // CONTROLLERPREFERENCESAPP_H
