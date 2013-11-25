#pragma once

// Qt stuff
#include <QObject>
#include <QSharedPointer>
#include <QString>
#include <QVariantList>
#include <QUrl>

#include "../Model/model_repository.h"
#include "controller_icons.h"

namespace GANN_MVC
{

class ControllerRepository: public QObject
{
    Q_OBJECT

public:
    ControllerRepository( );

    Q_PROPERTY(QUrl currentPathRepo READ GetCurrentPathRepo WRITE SetCurrentPathRepo NOTIFY currentPathRepoChanged)

    QUrl                    GetCurrentPathRepo() { return currentPathRepo; };
    void                    SetCurrentPathRepo(QUrl path) { currentPathRepo = path; emit currentPathRepoChanged(path);};

    /** @brief берет состояние репозитория */
    Q_INVOKABLE QVariant    GetStateRepository(QVariant path) const;

    /** @brief путь до репозитория по умолчанию */
    Q_INVOKABLE QVariant    GetDefaultRepositoryPath() const;

    /** @brief Начать клонирование репозитория */
    Q_INVOKABLE QVariant    StartCloneRepository(QVariant localUlr, QVariant remoteURL, QVariant nameRepo);

    /** @brief Отмена клонирования репозитория */
    Q_INVOKABLE void        CancelCloneRepository() const;

    /** @brief взять контент у файла(директории)*/
    Q_INVOKABLE QVariant    GetContentDirectory(QUrl dir) const;

    /** @brief удалить контент у файла(директории)*/
    Q_INVOKABLE QVariant    DropContentDirectory(QUrl dir) const;

    /** @brief явяеться ли выбранный путь поддиректорией корневого пути репозитория*/
    Q_INVOKABLE QVariant    DirIsSubRootDirRepository(QVariant dir) const;

    /** @brief возвращает последнее сообщение об ошибке */
    Q_INVOKABLE const QVariant GetLastError() const;

private:
    const QSharedPointer<ModelQmlAndCRepository>  model;
    QUrl                    currentPathRepo;

signals:
    void                    currentPathRepoChanged(QUrl);
};

}
