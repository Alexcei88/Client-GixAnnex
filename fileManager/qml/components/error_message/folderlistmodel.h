#ifndef FOLDERLISTMODEL_H
#define FOLDERLISTMODEL_H

#include <QDirModel>
#include <QDebug>
#include <QUrl>
#include <QQmlParserStatus>
#include <QObject>
#include <QFileSystemModel>

class FolderListModelPrivate;

class NewFolderListModel: public QAbstractListModel, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus)

    Q_PROPERTY(QUrl folder READ folder WRITE setFolder NOTIFY folderChanged)
    Q_PROPERTY(QUrl parentFolder READ parentFolder NOTIFY folderChanged)
    Q_PROPERTY(QStringList nameFilters READ nameFilters WRITE setNameFilters)
    Q_PROPERTY(SortField sortField READ sortField WRITE setSortField)
    Q_PROPERTY(bool sortReversed READ sortReversed WRITE setSortReversed)
//    Q_PROPERTY(bool showDirs READ showDirs WRITE setShowDirs)
//    Q_PROPERTY(bool showDotAndDotDot READ showDotAndDotDot WRITE setShowDotAndDotDot)
//    Q_PROPERTY(bool showOnlyReadable READ showOnlyReadable WRITE setShowOnlyReadable)
//    Q_PROPERTY(int count READ count)

public:
    NewFolderListModel(QObject *parent);
    ~NewFolderListModel();

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


    Q_INVOKABLE bool isFolder(int index) const;

    virtual void        classBegin();
    virtual void        componentComplete();

signals:
    void                folderChanged();

private slots:
    void                refresh();
    void                inserted(const QModelIndex &index, int start, int end);
    void                removed(const QModelIndex &index, int start, int end);
    void                handleDataChanged(const QModelIndex &start, const QModelIndex &end);

private:
    Q_DISABLE_COPY(NewFolderListModel);
    FolderListModelPrivate* d;

};


class FolderListModelPrivate
{

public:
    FolderListModelPrivate();

    // обновления сортировки
    void                UpdateSorting();

    QDirModel model;
    QUrl folder;
    QStringList nameFilters;
    QModelIndex folderIndex;
    NewFolderListModel::SortField sortField;
    bool sortReversed;
    int count;
};
#endif // FOLDERLISTMODEL_H
