#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractListModel>

class TreeModelItem;
class TreeModel : public QAbstractListModel
{
    Q_OBJECT

    enum ListMenuItemRoles
    {
        NameRole = Qt::UserRole+1,
        LevelRole,
        IsOpenedRole,
        HasChildrenRole
    };
public:
    explicit TreeModel(QObject *parent=0);
    // установка новых данных
    Q_INVOKABLE bool setData(const int& _index, const QString& fieldName, QVariant newValue);

    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QHash<int, QByteArray> roleNames() const;


public slots:

    void openItem(int numIndex);
    void closeItem(int numIndex);

private:

    Q_DISABLE_COPY(TreeModel)
    QList<TreeModelItem *> items;

    QHash<int, QByteArray> roles_;
};

#endif // TREEMODEL_H
