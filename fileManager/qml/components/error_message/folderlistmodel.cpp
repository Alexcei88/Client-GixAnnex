#include "folderlistmodel.h"

//----------------------------------------------------------------------------------------/
/*********************  FolderListModelPrivate  ******************************************/
//----------------------------------------------------------------------------------------/
FolderListModelPrivate::FolderListModelPrivate():
    sortField(NewFolderListModel::Name)
   ,sortReversed(false)
   ,count(0)
{
    nameFilters << QLatin1String("*");
}
//----------------------------------------------------------------------------------------/
void FolderListModelPrivate::UpdateSorting()
{
    QDir::SortFlags flags = 0;
    switch(sortField)
    {
    case NewFolderListModel::Unsorted:
        flags |= QDir::Unsorted;
        break;
    case NewFolderListModel::Name:
        flags |= QDir::Name;
        break;
    case NewFolderListModel::Time:
        flags |= QDir::Time;
        break;
    case NewFolderListModel::Size:
        flags |= QDir::Size;
        break;
    case NewFolderListModel::Type:
        flags |= QDir::Type;
        break;
    }

    if (sortReversed)
        flags |= QDir::Reversed;

    model.setSorting(flags);
}
//----------------------------------------------------------------------------------------/
/*********************   NewFolderListModel  **********************************************/
//----------------------------------------------------------------------------------------/
NewFolderListModel::NewFolderListModel(QObject *parent):
    QAbstractListModel(parent)
{
    d = new FolderListModelPrivate();
}
//----------------------------------------------------------------------------------------/
NewFolderListModel::~NewFolderListModel()
{
    delete d;
}
//----------------------------------------------------------------------------------------/
void NewFolderListModel::classBegin()
{

}
//----------------------------------------------------------------------------------------/
void NewFolderListModel::componentComplete()
{

}
//----------------------------------------------------------------------------------------/
QUrl NewFolderListModel::folder() const
{
    return d->folder;
}
//----------------------------------------------------------------------------------------/
void NewFolderListModel::setFolder(const QUrl &folder)
{
    if (folder == d->folder)
        return;
    QModelIndex index = d->model.index(folder.toLocalFile());
    if ((index.isValid() && d->model.isDir(index)) || folder.toLocalFile().isEmpty())
    {
        d->folder = folder;
        QMetaObject::invokeMethod(this, "refresh", Qt::QueuedConnection);
        emit folderChanged();
    }
}
//----------------------------------------------------------------------------------------/
QUrl NewFolderListModel::parentFolder() const
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
QStringList NewFolderListModel::nameFilters() const
{
    return d->nameFilters;
}
//----------------------------------------------------------------------------------------/
void NewFolderListModel::setNameFilters(const QStringList &filters)
{
    d->nameFilters = filters;
    d->model.setNameFilters(d->nameFilters);
}
//----------------------------------------------------------------------------------------/
NewFolderListModel::SortField NewFolderListModel::sortField() const
{
    return d->sortField;
}
//----------------------------------------------------------------------------------------/
void NewFolderListModel::setSortField(SortField field)
{
    if (field != d->sortField) {
        d->sortField = field;
        d->UpdateSorting();
    }
}
//----------------------------------------------------------------------------------------/
bool NewFolderListModel::sortReversed() const
{
    return d->sortReversed;
}
//----------------------------------------------------------------------------------------/
void NewFolderListModel::setSortReversed(bool rev)
{
    if (rev != d->sortReversed)
    {
        d->sortReversed = rev;
        d->UpdateSorting();
    }
}
//----------------------------------------------------------------------------------------/
bool NewFolderListModel::isFolder(int index) const
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
void NewFolderListModel::refresh()
{
    d->folderIndex = QModelIndex();
    if (d->count)
    {
        emit beginRemoveRows(QModelIndex(), 0, d->count-1);
        d->count = 0;
        emit endRemoveRows();
    }
    d->folderIndex = d->model.index(d->folder.toLocalFile());
    int newcount = d->model.rowCount(d->folderIndex);
    if (newcount) {
        emit beginInsertRows(QModelIndex(), 0, newcount-1);
        d->count = newcount;
        emit endInsertRows();
    }
}
//----------------------------------------------------------------------------------------/
void NewFolderListModel::inserted(const QModelIndex &index, int start, int end)
{
    if (index == d->folderIndex) {
        emit beginInsertRows(QModelIndex(), start, end);
        d->count = d->model.rowCount(d->folderIndex);
        emit endInsertRows();
    }
}
//----------------------------------------------------------------------------------------/
void NewFolderListModel::removed(const QModelIndex &index, int start, int end)
{
    if (index == d->folderIndex)
    {
        emit beginRemoveRows(QModelIndex(), start, end);
        d->count = d->model.rowCount(d->folderIndex);
        emit endRemoveRows();
    }
}
//----------------------------------------------------------------------------------------/
void NewFolderListModel::handleDataChanged(const QModelIndex &start, const QModelIndex &end)
{
    if (start.parent() == d->folderIndex)
        emit dataChanged(index(start.row(),0), index(end.row(),0));
}
//----------------------------------------------------------------------------------------/
bool NewFolderListModel::showDirs() const
{
    return d->model.filter() & QDir::AllDirs;
}
//----------------------------------------------------------------------------------------/
void NewFolderListModel::setShowDirs(bool on)
{
    if (!(d->model.filter() & QDir::AllDirs) == !on)
        return;
    if (on)
        d->model.setFilter(d->model.filter() | QDir::AllDirs | QDir::Drives);
    else
        d->model.setFilter(d->model.filter() & ~(QDir::AllDirs | QDir::Drives));
}

//----------------------------------------------------------------------------------------/
bool NewFolderListModel::showDotAndDotDot() const
{
    return !(d->model.filter() & QDir::NoDotAndDotDot);
}
//----------------------------------------------------------------------------------------/
void NewFolderListModel::setShowDotAndDotDot(bool on)
{
    if (!(d->model.filter() & QDir::NoDotAndDotDot) == on)
        return;
    if (on)
        d->model.setFilter(d->model.filter() & ~QDir::NoDotAndDotDot);
    else
        d->model.setFilter(d->model.filter() | QDir::NoDotAndDotDot);
}
//----------------------------------------------------------------------------------------/
bool NewFolderListModel::showOnlyReadable() const
{
    return d->model.filter() & QDir::Readable;
}
//----------------------------------------------------------------------------------------/
void NewFolderListModel::setShowOnlyReadable(bool on)
{
    if (!(d->model.filter() & QDir::Readable) == !on)
        return;
    if (on)
        d->model.setFilter(d->model.filter() | QDir::Readable);
    else
        d->model.setFilter(d->model.filter() & ~QDir::Readable);
}
//----------------------------------------------------------------------------------------/
