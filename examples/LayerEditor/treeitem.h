#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>

class TreeItem
{
public:
    explicit TreeItem(const QVector<QVariant>& data, TreeItem* parent = nullptr);
    ~TreeItem();

    TreeItem* child(int number);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    bool insertChildren(int position, int count, int columns);
    TreeItem* parent();
    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);
    int childNumber() const;
    bool setData(int column, const QVariant& value);

private:
    QList<TreeItem*> childItems;
    QVector<QVariant> itemData;
    TreeItem* parentItem;
};

#endif // TREEITEM_H
