#ifndef TREEMODEL_H
#define TREEMODEL_H

#include "treeitem.h"
#include <QAbstractItemModel>

class TreeModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    TreeModel(QObject* parent = nullptr);
    TreeModel(const QStringList& headers, const QVector<QVariant>& data, QObject* parent = nullptr);
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

private:
    void setupModelData(const QVector<QVariant>& data, TreeItem* parent);
    TreeItem* getItem(const QModelIndex& index) const;

    TreeItem* rootItem;
};

#endif // TREEMODEL_H
