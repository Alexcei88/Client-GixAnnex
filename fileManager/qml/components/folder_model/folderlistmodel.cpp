#include "folderlistmodel.h"
#include <iostream>
//----------------------------------------------------------------------------------------/
/*********************  QMLFolderListModelPrivate  ******************************************/
//----------------------------------------------------------------------------------------/
QMLFolderListModelPrivate::QMLFolderListModelPrivate():
    sortField(QMLFolderListModel::Name)
   ,sortReversed(false)
   ,count(0)
{
    nameFilters << QLatin1String("*");
    // запрещаем разруливание символических ссылок(нам это не нужно)
    model.setResolveSymlinks(false);
}
//----------------------------------------------------------------------------------------/
void QMLFolderListModelPrivate::UpdateSorting()
{
    QDir::SortFlags flags = 0;
    switch(sortField)
    {
    case QMLFolderListModel::Unsorted:
        flags |= QDir::Unsorted;
        break;
    case QMLFolderListModel::Name:
        flags |= QDir::Name;
        break;
    case QMLFolderListModel::Time:
        flags |= QDir::Time;
        break;
    case QMLFolderListModel::Size:
        flags |= QDir::Size;
        break;
    case QMLFolderListModel::Type:
        flags |= QDir::Type;
        break;
    }

    if (sortReversed)
        flags |= QDir::Reversed;

    model.setSorting(flags);
}
//----------------------------------------------------------------------------------------/
/*********************   QMLFolderListModel  **********************************************/
//----------------------------------------------------------------------------------------/
QMLFolderListModel::QMLFolderListModel(QObject *parent):
    QAbstractListModel(parent)
  , status_(Null)
{
    roles_[FileNameRole] = "fileName";
    roles_[FilePathRole] = "filePath";
    d = new QMLFolderListModelPrivate();

    d->model.setFilter(QDir::AllDirs | QDir::Files | QDir::System );
    connect(&d->model, SIGNAL(rowsInserted(const QModelIndex&,int,int))
            , this, SLOT(inserted(const QModelIndex&,int,int)));
    connect(&d->model, SIGNAL(rowsRemoved(const QModelIndex&,int,int))
            , this, SLOT(removed(const QModelIndex&,int,int)));
    connect(&d->model, SIGNAL(dataChanged(const QModelIndex&,const QModelIndex&))
            , this, SLOT(handleDataChanged(const QModelIndex&,const QModelIndex&)));
    connect(&d->model, SIGNAL(modelReset()), this, SLOT(refresh()));
    connect(&d->model, SIGNAL(layoutChanged()), this, SLOT(refresh()));
    connect(&watcher, SIGNAL(directoryChanged(QString)), this, SLOT(fullRefresh()), Qt::DirectConnection);
    connect(&watcher, SIGNAL(fileChanged(QString)), this, SLOT(fullRefresh()), Qt::DirectConnection);

    setShowDotAndDotDot(false);
}
//----------------------------------------------------------------------------------------/
QMLFolderListModel::~QMLFolderListModel()
{
    if(!d->folder.isEmpty())
        watcher.removePath(d->folder.toLocalFile());
    delete d;
}
//----------------------------------------------------------------------------------------/
void QMLFolderListModel::classBegin()
{

}
//----------------------------------------------------------------------------------------/
void QMLFolderListModel::componentComplete()
{
    if (!d->folder.isValid() || d->folder.toLocalFile().isEmpty() || !QDir().exists(d->folder.toLocalFile()))
        d->count = 0;

    if (!d->folderIndex.isValid())
    {
        d->model.refresh();
    }
}
//----------------------------------------------------------------------------------------/
QUrl QMLFolderListModel::folder() const
{
    return d->folder;
}
//----------------------------------------------------------------------------------------/
void QMLFolderListModel::setFolder(const QUrl &folder)
{
    if (folder == d->folder)
        return;

    QUrl oldFolder = d->folder;
    QModelIndex index = d->model.index(folder.toLocalFile());
    if ((index.isValid() && d->model.isDir(index)) || folder.toLocalFile().isEmpty())
    {
        d->folder = folder;
        // настраиваем watcher
        if(!oldFolder.isEmpty())
        {
            // удаляем старый путь, за которым следили
            watcher.removePath(oldFolder.toLocalFile());
        }
        watcher.addPath(folder.toLocalFile());
        d->model.refresh();
    }
}
//----------------------------------------------------------------------------------------/
QUrl QMLFolderListModel::parentFolder() const
{
    QString localFile = d->folder.toLocalFile();
    if (!localFile.isEmpty())
    {
        QDir dir(localFile);
#if defined(Q_OS_SYMBIAN) || defined(Q_OS_WIN)
        if (dir.isRoot())
            dir.setPath("");
        else
#endif
            dir.cdUp();
        localFile = dir.path();
    }
    else
    {
        int pos = d->folder.path().lastIndexOf(QLatin1Char('/'));
        if (pos == -1)
            return QUrl();
        localFile = d->folder.path().left(pos);
    }
    return QUrl::fromLocalFile(localFile);
}
//----------------------------------------------------------------------------------------/
QStringList QMLFolderListModel::nameFilters() const
{
    return d->nameFilters;
}
//----------------------------------------------------------------------------------------/
void QMLFolderListModel::setNameFilters(const QStringList &filters)
{
    d->nameFilters = filters;
    d->model.setNameFilters(d->nameFilters);
}
//----------------------------------------------------------------------------------------/
QMLFolderListModel::SortField QMLFolderListModel::sortField() const
{
    return d->sortField;
}
//----------------------------------------------------------------------------------------/
void QMLFolderListModel::setSortField(SortField field)
{
    if (field != d->sortField) {
        d->sortField = field;
        d->UpdateSorting();
    }
}
//----------------------------------------------------------------------------------------/
bool QMLFolderListModel::sortReversed() const
{
    return d->sortReversed;
}
//----------------------------------------------------------------------------------------/
void QMLFolderListModel::setSortReversed(bool rev)
{
    if (rev != d->sortReversed)
    {
        d->sortReversed = rev;
        d->UpdateSorting();
    }
}
//----------------------------------------------------------------------------------------/
bool QMLFolderListModel::isFolder(int index) const
{
    if (index != -1)
    {
        QModelIndex idx = d->model.index(index, 0, d->folderIndex);
        if (idx.isValid())
            return d->model.isDir(idx);
    }
    return false;
}
//----------------------------------------------------------------------------------------/
void QMLFolderListModel::updateModel()
{
    QMetaObject::invokeMethod(this, "refresh", Qt::DirectConnection);
}
//----------------------------------------------------------------------------------------/
void QMLFolderListModel::refresh()
{
    status_ = Null;
    emit statusChanged(status_);

    d->folderIndex = QModelIndex();
    if (d->count)
    {
        emit beginRemoveRows(QModelIndex(), 0, d->count-1);
        d->count = 0;
        emit endRemoveRows();
    }
    if(d->folder.toLocalFile().isEmpty())
    {
        // указан невалидный путь
        d->count = 0;
    }
    else
    {
        d->folderIndex = d->model.index(d->folder.toLocalFile());
        int newcount = d->model.rowCount(d->folderIndex);
        if (newcount) {
            emit beginInsertRows(QModelIndex(), 0, newcount-1);
            d->count = newcount;
            emit endInsertRows();
        }
    }
    status_ = Ready;
    emit statusChanged(status_);
}
//----------------------------------------------------------------------------------------/
void QMLFolderListModel::fullRefresh()
{
    d->model.refresh();
}
//----------------------------------------------------------------------------------------/
void QMLFolderListModel::inserted(const QModelIndex &index, int start, int end)
{
    if (index == d->folderIndex)
    {
        emit beginInsertRows(QModelIndex(), start, end);
        d->count = d->model.rowCount(d->folderIndex);
        emit endInsertRows();
    }
}
//----------------------------------------------------------------------------------------/
void QMLFolderListModel::removed(const QModelIndex &index, int start, int end)
{
    if (index == d->folderIndex)
    {
        emit beginRemoveRows(QModelIndex(), start, end);
        d->count = d->model.rowCount(d->folderIndex);
        emit endRemoveRows();
    }
}
//----------------------------------------------------------------------------------------/
void QMLFolderListModel::handleDataChanged(const QModelIndex &start, const QModelIndex &end)
{
    if (start.parent() == d->folderIndex)
        emit dataChanged(index(start.row(),0), index(end.row(),0));
}
//----------------------------------------------------------------------------------------/
bool QMLFolderListModel::showDirs() const
{
    return d->model.filter() & QDir::AllDirs;
}
//----------------------------------------------------------------------------------------/
void QMLFolderListModel::setShowDirs(bool on)
{
    if (!(d->model.filter() & QDir::AllDirs) == !on)
        return;
    if (on)
        d->model.setFilter(d->model.filter() | QDir::AllDirs | QDir::Drives);
    else
        d->model.setFilter(d->model.filter() & ~(QDir::AllDirs | QDir::Drives));
}

//----------------------------------------------------------------------------------------/
bool QMLFolderListModel::showDotAndDotDot() const
{
    return !(d->model.filter() & QDir::NoDotAndDotDot);
}
//----------------------------------------------------------------------------------------/
void QMLFolderListModel::setShowDotAndDotDot(bool on)
{
    if (!(d->model.filter() & QDir::NoDotAndDotDot) == on)
        return;
    if (on)
        d->model.setFilter(d->model.filter() & ~QDir::NoDotAndDotDot);
    else
        d->model.setFilter(d->model.filter() | QDir::NoDotAndDotDot);
}
//----------------------------------------------------------------------------------------/
bool QMLFolderListModel::showOnlyReadable() const
{
    return d->model.filter() & QDir::Readable;
}
//----------------------------------------------------------------------------------------/
void QMLFolderListModel::setShowOnlyReadable(bool on)
{
    if (!(d->model.filter() & QDir::Readable) == !on)
        return;
    if (on)
        d->model.setFilter(d->model.filter() | QDir::Readable);
    else
        d->model.setFilter(d->model.filter() & ~QDir::Readable);
}
//----------------------------------------------------------------------------------------/
bool QMLFolderListModel::showDirsFirst() const
{
    return d->model.sorting() & QDir::DirsFirst;
}
//----------------------------------------------------------------------------------------/
void QMLFolderListModel::setShowDirsFirst(bool on)
{
    if (!(d->model.sorting() & QDir::DirsFirst) == !on)
        return;
    if (on)
        d->model.setSorting(d->model.sorting() | QDir::DirsFirst);
    else
        d->model.setSorting(d->model.sorting() & ~QDir::DirsFirst);
}
//----------------------------------------------------------------------------------------/
int QMLFolderListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return d->count;
}
//----------------------------------------------------------------------------------------/
QVariant QMLFolderListModel::data(const QModelIndex &index, int role) const
{
    QVariant rv;
    QModelIndex modelIndex = d->model.index(index.row(), 0, d->folderIndex);

    if (modelIndex.isValid())
    {
        if (role == FileNameRole)
            rv = d->model.data(modelIndex, QDirModel::FileNameRole).toString();
         else if (role == FilePathRole)
            rv = QUrl::fromLocalFile(d->model.data(modelIndex, QDirModel::FilePathRole).toString());
    }
    return rv;
}
//----------------------------------------------------------------------------------------/
QHash<int, QByteArray> QMLFolderListModel::roleNames() const
{
    return roles_;
}
//----------------------------------------------------------------------------------------/
