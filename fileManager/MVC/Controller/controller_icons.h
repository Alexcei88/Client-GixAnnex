#ifndef CONTROLLER_ICONS_H
#define CONTROLLER_ICONS_H

/*
 * Класс КОНТРОЛЛЕР ИКОНОК, задача которого
 * 1. генерация путей дя загрузки нужных иконок в QML
 * например, в зависимости от MimeType будет разные иконки грузиться
 * 2. актуализация состояния иконок синхронизации(если у файла поменялось
 * состояние синхронизации, то немедленно передать в представление)
*/

#include <QSharedPointer>

#include "../Model/model_repository.h"
#include "../Model/model_icons.h"

#include <QUrl>

namespace GANN_MVC
{

class ControllerIcons : public QObject
{
    Q_OBJECT
public:
    ControllerIcons();
    ~ControllerIcons();

    /** @brief текущий отображаемый путь */
    Q_PROPERTY(QUrl currentPath READ GetCurrentPath WRITE SetCurrentPath NOTIFY changedParentDirectory);

    void                SetCurrentPath(QUrl curPath) { currentPathView = curPath; emit changedParentDirectory(curPath);};
    QUrl                GetCurrentPath() { return currentPathView; };

    /** @brief вектор состояний иконок */
    Q_PROPERTY(QVariantMap stateIconsFileSyncQML READ GetStateIconsFileSync NOTIFY changedStateIconsFileSync);

    QVariantMap         GetStateIconsFileSync() { return stateIconsFileSync; };

    /** @brief возвращает путь иконки для проводника в зависимости от mimetype файла
    @param file - путь к файлу */
    Q_INVOKABLE QVariant getPathIconsFileDirectoryView(QUrl file) const;

    /** @brief возвращает путь иконки для тображения иконки в свойствах файла в зависимости от mimetype файла
    @param file - путь к файлу */
    Q_INVOKABLE QVariant getPathIconsFilePropertyFile(QUrl file) const;

    /** @brief дата последней модификации файла(директории)
    @param file - путь к файлу */
    Q_INVOKABLE QVariant getLastModifiedFile(QUrl file) const;

    /** @brief размер файла(директории)
    @param file - путь к файлу */
    Q_INVOKABLE QVariant getSizeFile(QUrl file) const;

    /** @brief  Запуск потока обновления иконок синхронизации */
    Q_INVOKABLE void    startThreadIconsSync();

    /** @brief полностью обновить список состояния иконок(вектор состояний иконок) */
    void                UpdateStateIconsFileSync();

    /** @brief Возвращает новый список */
    //Q_INVOKABLE QVariantList makeNewList() { QVariantList listNew; listNew.push_back("synced"); return listNew;};

public slots:
    void                OnChangeParentDirectory(QUrl curDir);

private:
    // модели
    const QSharedPointer<ModelQmlAndCRepository>  mainModel;
    ModelQmlAndCIcons*  modelIcons;

    /** @brief список текущего состояния иконок синхронизации
    * в зависимости от текущего списка отображаемых иконок файлов(директорий) */
    QVariantMap         stateIconsFileSync;

    /** @brief текущий отображаемый путь в модели QML FolderListModel */
    QUrl                currentPathView;
    // вспомог класс
    QDir                dir;

signals:
    void                changedStateIconsFileSync(QVariantList);
    void                changedParentDirectory(QUrl);
};

}
#endif // CONTROLLER_ICONS_H
