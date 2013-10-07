#pragma once

// Qt stuff
#include <QObject>
#include <QSharedPointer>
#include <QString>
#include <QVariantList>

#include "../Model/model_repository.h"
namespace GANN_MVC
{

class ControllerRepository: public QObject
{
    Q_OBJECT

public:
    ControllerRepository( );

    Q_PROPERTY(QString currentPathRepo READ GetCurrentPathRepo WRITE SetCurrentPathRepo NOTIFY currentPathRepoChanged)

    QString                 GetCurrentPathRepo() { return currentPathRepo; };
    void                    SetCurrentPathRepo(QString path) { currentPathRepo = path; emit currentPathRepoChanged(path);};

    /** @brief берет состояние объекта */
    Q_INVOKABLE QVariantList GetStateListRepository() const;

    /** @brief путь до репозитория по умолчанию */
    Q_INVOKABLE QVariant     GetDefaultRepositoryPath() const;

    /** @brief Начать клонирование репозитория */
    Q_INVOKABLE QVariant    StartCloneRepository(QVariant localUlr, QVariant remoteURL, QVariant nameRepo);

    /** @brief Отмена клонирования репозитория */
    Q_INVOKABLE void        CancelCloneRepository() const;

    /** @brief взять контент у файла(директории)*/
    Q_INVOKABLE QVariant    GetContentDirectory(QVariant dir) const;

    /** @brief удалить контент у файла(директории)*/
    Q_INVOKABLE QVariant    DropContentDirectory(QVariant dir) const;

private:
    const QSharedPointer<ModelQmlAndCRepository>  model;
    QString                 currentPathRepo;
signals:
    void                currentPathRepoChanged(QString);
};

}
