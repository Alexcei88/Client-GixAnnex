#ifndef FOLDERLISTMODEL_H
#define FOLDERLISTMODEL_H

#include <QDirModel>
#include <QDebug>
#include <QUrl>
#include <QQmlParserStatus>
#include <QObject>
#include <QFileSystemModel>

class QMLFolderListModelPrivate;

class QMLFolderListModel: public QAbstractListModel, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)

    Q_PROPERTY(QUrl folder READ folder WRITE setFolder NOTIFY folderChanged)
    Q_PROPERTY(QUrl parentFolder READ parentFolder NOTIFY folderChanged)
    Q_PROPERTY(QStringList nameFilters READ nameFilters WRITE setNameFilters)
    Q_PROPERTY(SortField sortField READ sortField WRITE setSortField)
    Q_PROPERTY(bool sortReversed READ sortReversed WRITE setSortReversed)
    Q_PROPERTY(bool showDirs READ showDirs WRITE setShowDirs)
    Q_PROPERTY(bool showDotAndDotDot READ showDotAndDotDot WRITE setShowDotAndDotDot)
    Q_PROPERTY(bool showOnlyReadable READ showOnlyReadable WRITE setShowOnlyReadable)
    Q_PROPERTY(bool showDirsFirst READ showDirsFirst WRITE setShowDirsFirst)
    Q_PROPERTY(int count READ count)

    enum Roles
    {
        FileNameRole = Qt::UserRole + 1,
        FilePathRole
    };

public:
    QMLFolderListModel(QObject *parent = 0);
    ~QMLFolderListModel();

    QUrl                folder() const;
    void                setFolder(const QUrl &folder);

    QUrl                parentFolder() const;

    QStringList         nameFilters() const;
    void                setNameFilters(const QStringList &filters);

    enum SortField { Unsorted, Name, Time, Size, Type };
    Q_ENUMS(SortField)

    SortField           sortField() const;
    void                setSortField(SortField field);

    bool                sortReversed() const;
    void                setSortReversed(bool rev);

    bool                showDirs() const;
    void                setShowDirs(bool);
    bool                showDotAndDotDot() const;
    void                setShowDotAndDotDot(bool);
    bool                showOnlyReadable() const;
    void                setShowOnlyReadable(bool);
    bool                showDirsFirst() const;
    void                setShowDirsFirst(bool);

    int                 count() const { return rowCount(QModelIndex()); }

    /** @brief переопределяемые методы абстрактной модели */
    int                 rowCount(const QModelIndex &parent) const;
    QVariant            data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    virtual void        classBegin();
    virtual void        componentComplete();

    Q_INVOKABLE bool    isFolder(int index) const;
    // обновить модель
    Q_INVOKABLE void    updateModel();

signals:
    void                folderChanged();

private slots:
    void                refresh();
    void                inserted(const QModelIndex &index, int start, int end);
    void                removed(const QModelIndex &index, int start, int end);
    void                handleDataChanged(const QModelIndex &start, const QModelIndex &end);

private:
    Q_DISABLE_COPY(QMLFolderListModel);
    QMLFolderListModelPrivate* d;
    QHash<int, QByteArray> roles_;

};


class QMLFolderListModelPrivate
{
public:
    QMLFolderListModelPrivate();

    // обновления способа сортировки
    void                UpdateSorting();

    QDirModel           model;
    QUrl                folder;
    QStringList         nameFilters;
    QModelIndex         folderIndex;
    QMLFolderListModel::SortField sortField;
    bool                sortReversed;
    int                 count;
};
#endif // FOLDERLISTMODEL_H
