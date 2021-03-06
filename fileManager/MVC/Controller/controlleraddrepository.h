#ifndef CONTROLLERADDREPOSITORY_H
#define CONTROLLERADDREPOSITORY_H

// Qt stuff
#include <QObject>
#include <QMap>
#include <QVariant>

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

    /** @brief вектор состояний иконок */
    Q_PROPERTY(QVariantList options READ GetListOptions);

    const QVariantList GetListOptions();

    /** @brief Добавление опции в вектор */
    Q_INVOKABLE void    setOptions(const QVariant key, const QVariant value);

    /** @brief Взять значение опции */
    Q_INVOKABLE QVariant getOptions(const QVariant key);

    /** @brief Выбран репозиторий */
    Q_INVOKABLE void    selectServer(const QVariant index);

    /** @brief Старт добавления репозитория */
    Q_INVOKABLE void    startAddRepository() const;

    /** @brief Закрыть окно добавления репозитория */
    Q_INVOKABLE void    cancelAddRepository() const;

    /** @brief Закрыть окно добавления репозитория */
    Q_INVOKABLE void    closeAddRepository() const;




private:
    std::shared_ptr<IModelQmlAndCAddRepository> model;
    // параметры копирования
    QMap<QString, QString> options;

};

}
#endif // CONTROLLERADDREPOSITORY_H
