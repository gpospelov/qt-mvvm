#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>
#include <QVector>

class TreeItem
{
public:
    enum TYPE { Layer, Assembly };
    TreeItem(TYPE type, const QVector<QVariant>& data, TreeItem* parent = nullptr);
    virtual ~TreeItem();

    TreeItem* parent() const;
    void setParent(TreeItem* parent) { parentItem = parent; }
    TYPE type() const { return m_type; }

    // children
    TreeItem* child(int number);
    int childCount() const;
    int childNumber() const;
    virtual bool insertChildren(int position, int count, TYPE type) = 0;
    bool insertChild(int position, TreeItem* child);
    bool removeChildren(int position, int count);

    // data
    int columnCount() const;
    QVariant data(int column) const;
    bool setData(int column, const QVariant& value);

protected:
    QList<TreeItem*> childItems;

private:
    TYPE m_type;
    QVector<QVariant> itemData;
    TreeItem* parentItem;
};

class LayerItem : public TreeItem
{
public:
    explicit LayerItem(TreeItem* parent = nullptr);
    ~LayerItem() override = default;

    bool insertChildren(int, int, TYPE) override { return false; }
};

class AssemblyItem : public TreeItem
{
public:
    explicit AssemblyItem(TreeItem* parent = nullptr);
    ~AssemblyItem() override = default;

    bool insertChildren(int position, int count, TYPE type) override;
};

#endif // TREEITEM_H
