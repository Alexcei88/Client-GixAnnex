#include "treemodel.h"

#include <iostream>
//----------------------------------------------------------------------------------------/
class TreeModelItem
{
public:
    TreeModelItem(QString name_ = QString()):
        name(name_),
        level(0),
        isOpened(false)
    {}

    void adjustChildrenLevels()
    {
        foreach(TreeModelItem *item, children)
        {
            item->level = level+1;
            item->adjustChildrenLevels();
        }
    }

    QString name;
    int level;
    bool isOpened;
    QList<TreeModelItem *> children;
    inline bool hasChildren() {return !children.empty();}
};
//----------------------------------------------------------------------------------------/
TreeModel::TreeModel(QObject *parent) :
    QAbstractListModel(parent)
{
    TreeModelItem *toAdd;
    items << new TreeModelItem("Choice");
    items << new TreeModelItem("Details");
    items << new TreeModelItem("Location");
    items << new TreeModelItem("Summary");
    items << new TreeModelItem("Processing");
    items << new TreeModelItem("Finish");

    // заполняем роли модели
    roles_.insert(NameRole, QByteArray("name"));
    roles_.insert(LevelRole, QByteArray("level"));
    roles_.insert(IsOpenedRole, QByteArray("isOpened"));
    roles_.insert(HasChildrenRole, QByteArray("hasChildren"));
}
//----------------------------------------------------------------------------------------/
QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    if(index.row() > (items.size()-1) )
        return QVariant();
    TreeModelItem *item = items.at(index.row());
    switch(role)
    {
        case Qt::DisplayRole:
        case NameRole:
            return QVariant::fromValue(item->name);

        case LevelRole:
            return QVariant::fromValue(item->level);

        case IsOpenedRole:
            return QVariant::fromValue(item->isOpened);

        case HasChildrenRole:
            return QVariant::fromValue(item->hasChildren());

        default:
            return QVariant();
    }
}
//----------------------------------------------------------------------------------------/
bool TreeModel::setData(const int& _index, const QString& fieldName, QVariant newValue)
{
    if (_index < 0 || _index > items.count())
      return false;

    if(fieldName == "name")
    {
        TreeModelItem* item = items.at(_index);
        item->name = newValue.toString();
        emit dataChanged(index(_index), index(_index));
        return true;
    }
    return false;
}
//----------------------------------------------------------------------------------------/
int TreeModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return items.size();
}
//----------------------------------------------------------------------------------------/
void TreeModel::openItem(int numIndex)
{
    if(numIndex > (items.size()-1))
        return;

    if(items[numIndex]->isOpened)
       return;

    QModelIndex modelIndex = index(numIndex);

    //Выставляем флаг открытого элемента
    items[numIndex]->isOpened = true;

    //Оповещаем QML-код об изменении данных
    emit dataChanged(modelIndex, modelIndex);

    int i = numIndex+1;

    //Оповещаем QML-код о том, что будут добавлены строки в модель
    beginInsertRows(QModelIndex(), i, i+items[numIndex]->children.size()-1);

    //Добавляем всех потомков элемента в модель после этого элемента
    foreach(TreeModelItem *item, items[numIndex]->children)
        items.insert(i++, item);

    //Оповещаем QML-код о том, что все строки добавлены
    endInsertRows();
}
//----------------------------------------------------------------------------------------/
void TreeModel::closeItem(int numIndex)
{
    if(numIndex > (items.size()-1))
        return;

    if(!items[numIndex]->isOpened)
        return;

    QModelIndex modelIndex = index(numIndex);

    //Сбрасываем флаг открытого элемента
    items[numIndex]->isOpened = false;

    //Оповещаем QML-код об изменении данных
    emit dataChanged(modelIndex, modelIndex);

    int i = numIndex+1;

    //Ищем все элементы после текущего с большим level
    //Таким образом найдем всех прямых и косвенных потомков
    for (; i < items.size() && (items[i]->level > items[numIndex]->level); ++i) {}
    --i;

    //Оповещаем QML-код о том, что будут удалены строки из модели
    beginRemoveRows(QModelIndex(), numIndex+1, i);

    //Удаляем все посчитанные элементы из модели и сбрасываем у них флаг открытия
    while (i > numIndex)
    {
        items[i]->isOpened = false;
        items.removeAt(i--);
    }

    //Оповещаем QML-код о том, что все строки удалены
    endRemoveRows();
}
//----------------------------------------------------------------------------------------/
QHash<int, QByteArray> TreeModel::roleNames() const
{
    return roles_;
}
//----------------------------------------------------------------------------------------/
