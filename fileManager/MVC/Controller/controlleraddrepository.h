#ifndef CONTROLLERADDREPOSITORY_H
#define CONTROLLERADDREPOSITORY_H

// Qt stuff
#include <QObject>
#include <QSharedPointer>

// our stuff
#include "../Model/AddRepository/imodeladdrepository.h"

namespace GANN_MVC
{
class ControllerAddRepository: public QObject
{
    Q_OBJECT
public:
    ControllerAddRepository();
    QSharedPointer<IModelQmlAndCAddRepository>  model;
};

}
#endif // CONTROLLERADDREPOSITORY_H
