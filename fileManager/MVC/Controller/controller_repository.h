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

    // путь до файла с конфигурацией репозиториев
    Q_PROPERTY(QVariant pathRepoConfig READ GetPathRepoConfig CONSTANT)

    QUrl                    GetCurrentPathRepo() { return currentPathRepo; };
    void                    SetCurrentPathRepo(QUrl path) { currentPathRepo = path; emit currentPathRepoChanged(path);};

    const QVariant          GetPathRepoConfig() const;

    /** @brief берет состояние репозитория */
    Q_INVOKABLE QVariant    getStateRepository(QUrl path) const;

    /** @brief Удаление репозитория */
    Q_INVOKABLE void        deleteRepository(QUrl path) const;

    /** @brief включает/выключает синхронизацию репозитория */
    Q_INVOKABLE void        setEnableRepository(bool enable) const;

    /** @brief есть ли команды у текущего репозитория */
    Q_INVOKABLE bool        isExecuteCommandForCurrentRepository() const;

    /** @brief путь до репозитория по умолчанию */
    Q_INVOKABLE QVariant    getDefaultRepositoryPath() const;

    /** @brief Начать клонирование репозитория */
    Q_INVOKABLE QVariant    startCloneRepository(QVariant localUlr, QVariant remoteURL, QVariant nameRepo);

    /** @brief Отмена клонирования репозитория */
    Q_INVOKABLE void        cancelCloneRepository() const;

    /** @brief взять контент у файла(директории)*/
    Q_INVOKABLE QVariant    getContentDirectory(QUrl dir) const;

    /** @brief удалить контент у файла(директории)*/
    Q_INVOKABLE QVariant    dropContentDirectory(QUrl dir) const;

    /** @brief удалить файл(директорию) из репозитория */
    Q_INVOKABLE QVariant    removeDirectory(QUrl dir) const;

    /** @brief явяеться ли выбранный путь поддиректорией корневого пути репозитория*/
    Q_INVOKABLE QVariant    dirIsSubRootDirRepository(QUrl dir) const;

private:
    const QSharedPointer<ModelQmlAndCRepository>  model;
    QUrl                    currentPathRepo;

signals:
    void                    currentPathRepoChanged(QUrl);
};

}
