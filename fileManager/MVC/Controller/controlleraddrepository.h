#ifndef CONTROLLERADDREPOSITORY_H
#define CONTROLLERADDREPOSITORY_H

// Qt stuff
#include <QObject>

// our stuff
#include "../Model/AddRepository/imodel_addrepository.h"

// std stuff
#include <memory>

namespace GANN_MVC
{
class ControllerAddRepository: public QObject
{
    Q_OBJECT
public:
    ControllerAddRepository();

    /** @brief выбран remote server */
    Q_INVOKABLE void    selectRemoteServer();

    /** @brief Отмена добавления репозитория */
    Q_INVOKABLE void    closeAddRepository() const;

private:
    std::shared_ptr<IModelQmlAndCAddRepository> model;

};

}
#endif // CONTROLLERADDREPOSITORY_H
