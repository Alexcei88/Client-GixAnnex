#ifndef CONTROLLER_ICONS_H
#define CONTROLLER_ICONS_H

/*
 * Класс КОНТРОЛЛЕР ИКОНОК, задача которого
 * 1. генерация путей дя загрузки нужных иконок в QML
 * например, в зависимости от MimeType будет разные иконки грузиться
 * 2. актуализация состояния иконок синхронизации(если у файла поменялось
 * состояние синхронизации, то немедленно передать в представление)
*/

#include <QObject>
#include <QSharedPointer>
#include <QVariant>
#include <QStringList>
#include <QDir>
#include <QTimer>

#include "../Model/model_repository.h"
#include "../Model/model_icons.h"

namespace GANN_MVC
{

class ControllerIcons : public QObject
{
    Q_OBJECT
public:
    ControllerIcons();
    ~ControllerIcons();

    /** @brief текущий отображаемый путь */
    Q_PROPERTY(QString currentPath READ GetCurrentPath WRITE SetCurrentPath NOTIFY changedParentDIrectory);

    void                SetCurrentPath(QString curPath) { currentPathView = curPath; emit changedParentDIrectory(curPath);};
    QString             GetCurrentPath() { return currentPathView; };

    /** @brief вектор состояний иконок */
    Q_PROPERTY(QVariantMap stateIconsFileSyncQML READ GetStateIconsFileSync WRITE SetStateIconsFileSync NOTIFY changedStateIconsFileSync);

    void                SetStateIconsFileSync(QVariantMap stateIcons) { stateIconsFileSync = stateIcons;};
    QVariantMap         GetStateIconsFileSync() { return stateIconsFileSync; };

    /** @brief возвращает путь иконки в зависимости от mimetype файла
    @param file - путь к файлу */
    Q_INVOKABLE QVariant GetPathIconsFile(QVariant file) const;

    /** @brief дата последней модификации файла(директории)
    @param file - путь к файлу */
    Q_INVOKABLE QVariant GetLastModifiedFile(QVariant file) const;

    /** @brief размер файла(директории)
    @param file - путь к файлу */
    Q_INVOKABLE QVariant GetSizeFile(QVariant file) const;

    /** @brief Возвращает новый список */
    //Q_INVOKABLE QVariantList makeNewList() { QVariantList listNew; listNew.push_back("synced"); return listNew;};

public slots:
    void                OnChangeParrentDirectory(QString curDir);

private:
    const QSharedPointer<ModelQmlAndCRepository>  mainModel;
    const QSharedPointer<ModelQmlAndCIcons> modelIcons;

    /** @brief список текущего состояния иконок синхронизации
    * в зависимости от текущего списка отображаемых иконок файлов(директорий) */
    QVariantMap        stateIconsFileSync;

    /** @brief текущий отображаемый путь в модели QML FolderListModel */
    QString             currentPathView;
    // вспомог класс
    QDir                dir;

    /** @brief полностью обновить список состояния иконок */
    void                UpdateStateIconsFileSync();

signals:
    void                changedStateIconsFileSync(QVariantList);
    void                changedParentDIrectory(QString);
    void                stopThread();
};

}
#endif // CONTROLLER_ICONS_H
