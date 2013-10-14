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
#include <QVariant>
#include <QStringList>
#include <QDir>

namespace GANN_MVC
{

class ControllerIcons : public QObject
{
    Q_OBJECT
public:
    ControllerIcons();

    /** @brief текущий отображаемый путь */
    Q_PROPERTY(QString currentPath READ GetCurrentPath WRITE SetCurrentPath NOTIFY changedCurrentPath);

    void                SetCurrentPath(QString curPath) { currentPathView = curPath; emit changedCurrentPath(curPath);};
    QString             GetCurrentPath() { return currentPathView; };

    /** @brief вектор состояний иконок */
    Q_PROPERTY(QVariantMap stateIconsFileSync READ GetStateIconsFileSync WRITE SetStateIconsFileSync NOTIFY changedStateIconsFileSync);

    void                SetStateIconsFileSync (QVariantMap stateIcons) { stateIconsFileSync = stateIcons;};
    QVariantMap        GetStateIconsFileSync() { return stateIconsFileSync; };

    /** @brief возвращает путь иконки в зависимости от mimetype файла
    @param file - путь к файлу */
    Q_INVOKABLE QVariant GetPathIconsFile(QVariant file) const;

    // тестовая функция
    Q_INVOKABLE QVariantList makeNewList() { QVariantList listNew; listNew.push_back("synced"); return listNew;};

public slots:
    void                OnChangeParrentDirectory(QString curDir);

private:
    /** @brief список текущего состояния иконок синхронизации
    * в зависимости от текущего списка отображаемых иконок файлов(директорий) */
    QVariantMap        stateIconsFileSync;

    /** @brief текущий отображаемый путь в модели QML FolderListModel */
    QString             currentPathView;

    QDir                dir;

    // полностью обновить список состояния иконок
    void                UpdateStateIconsFileSync();

    // обновить представление
    void                UpdateView();
signals:
    void                changedStateIconsFileSync(QVariantList);
    void                changedCurrentPath(QString);
};

}
#endif // CONTROLLER_ICONS_H
