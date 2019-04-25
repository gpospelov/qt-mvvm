#ifndef TREEMODEL_H
#define TREEMODEL_H

#include "treeitem.h"
#include <QAbstractItemModel>

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    TreeModel(TreeItem* root_item, QObject* parent = nullptr);
    TreeModel(QObject* parent = nullptr);
    ~TreeModel() override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column,
                      const QModelIndex& parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex& index) const override;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    bool insertRows(int position, int rows, const QModelIndex& parent = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex& parent = QModelIndex()) override;

    QSize span(const QModelIndex& index) const override;

    bool insertLayers(int rows, const QModelIndex& current_selection = QModelIndex());
    bool insertAssemblies(int rows, const QModelIndex& current_selection = QModelIndex());

private:
    TreeItem* getItem(const QModelIndex& index) const;
    void insertDefaultLayerIntoAssembly(const QModelIndex& current_selection);

    TreeItem* rootItem;
};

#endif // TREEMODEL_H
