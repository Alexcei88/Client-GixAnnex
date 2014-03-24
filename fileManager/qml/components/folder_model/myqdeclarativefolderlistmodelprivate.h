#ifndef MYQDECLARATIVEFOLDERLISTMODELPRIVATE_H
#define MYQDECLARATIVEFOLDERLISTMODELPRIVATE_H


#include <QDirModel>
#include <QDebug>
#include <QUrl>
#include <QtDeclarative/QDeclarativeParserInfo>
//#include <qdeclarativecontext.h>

class QDeclarativeFolderListModelPrivate;

class QDeclarativeFolderListModel : public QAbstractListModel, public QDeclarativeParserInfo
{
    Q_OBJECT
    Q_INTERFACES(QDeclarativeParserInfo)

    Q_PROPERTY(QUrl folder READ folder WRITE setFolder NOTIFY folderChanged)
    Q_PROPERTY(QUrl parentFolder READ parentFolder NOTIFY folderChanged)
    Q_PROPERTY(QStringList nameFilters READ nameFilters WRITE setNameFilters)
    Q_PROPERTY(SortField sortField READ sortField WRITE setSortField)
    Q_PROPERTY(bool sortReversed READ sortReversed WRITE setSortReversed)
    Q_PROPERTY(bool showDirs READ showDirs WRITE setShowDirs)
    Q_PROPERTY(bool showDotAndDotDot READ showDotAndDotDot WRITE setShowDotAndDotDot)
    Q_PROPERTY(bool showOnlyReadable READ showOnlyReadable WRITE setShowOnlyReadable)
    Q_PROPERTY(int count READ count)

public:
    QDeclarativeFolderListModel(QObject *parent = 0);
    ~QDeclarativeFolderListModel();

    enum Roles { FileNameRole = Qt::UserRole+1, FilePathRole = Qt::UserRole+2 };

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;

    int count() const { return rowCount(QModelIndex()); }

    QUrl folder() const;
    void setFolder(const QUrl &folder);

    QUrl parentFolder() const;

    QStringList nameFilters() const;
    void setNameFilters(const QStringList &filters);

    enum SortField { Unsorted, Name, Time, Size, Type };
    SortField sortField() const;
    void setSortField(SortField field);
    Q_ENUMS(SortField)

    bool sortReversed() const;
    void setSortReversed(bool rev);

    bool showDirs() const;
    void  setShowDirs(bool);
    bool showDotAndDotDot() const;
    void  setShowDotAndDotDot(bool);
    bool showOnlyReadable() const;
    void  setShowOnlyReadable(bool);

    Q_INVOKABLE bool isFolder(int index) const;

    virtual void classBegin();
    virtual void componentComplete();

Q_SIGNALS:
    void folderChanged();

private Q_SLOTS:
    void refresh();
    void inserted(const QModelIndex &index, int start, int end);
    void removed(const QModelIndex &index, int start, int end);
    void handleDataChanged(const QModelIndex &start, const QModelIndex &end);

private:
    Q_DISABLE_COPY(QDeclarativeFolderListModel)
    QDeclarativeFolderListModelPrivate *d;
};


class QDeclarativeFolderListModelPrivate
 {
 public:
     QDeclarativeFolderListModelPrivate()
         : sortField(QDeclarativeFolderListModel::Name), sortReversed(false), count(0) {
         nameFilters << QLatin1String("*");
     }
     ~QDeclarativeFolderListModelPrivate() {};

     void updateSorting() {
         QDir::SortFlags flags = 0;
         switch(sortField) {
         case QDeclarativeFolderListModel::Unsorted:
             flags |= QDir::Unsorted;
             break;
         case QDeclarativeFolderListModel::Name:
             flags |= QDir::Name;
             break;
         case QDeclarativeFolderListModel::Time:
             flags |= QDir::Time;
             break;
         case QDeclarativeFolderListModel::Size:
             flags |= QDir::Size;
             break;
         case QDeclarativeFolderListModel::Type:
             flags |= QDir::Type;
             break;
         }

         if (sortReversed)
             flags |= QDir::Reversed;

         model.setSorting(flags);
     }

     QDirModel model;
     QUrl folder;
     QStringList nameFilters;
     QModelIndex folderIndex;
     QDeclarativeFolderListModel::SortField sortField;
     bool sortReversed;
     int count;
 };


#endif // MYQDECLARATIVEFOLDERLISTMODELPRIVATE_H
