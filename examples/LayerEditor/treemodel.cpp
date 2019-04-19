#include "treemodel.h"
#include <QSize>

namespace {
QVector<QVariant> defaultLayerData()
{
    /*layer_name, material_name, thickness, roughness*/
    return {"layer", "default", 0.0, 0.0};
}

QVector<QVariant> defaultAssemblyData()
{
    /*assembly_name, number_of_repetitions*/
    return {"assembly", 1};
}
}

TreeModel::TreeModel(QObject* parent) : QAbstractItemModel(parent)
{
    QVector<QVariant> rootData{"Name", "Material", "Thickness", "Roughness"};
    rootItem = new TreeItem(rootData);

    QVector<QVariant> data = defaultLayerData();
    setupModelData(data, rootItem);
}

TreeModel::TreeModel(const QStringList& headers, const QVector<QVariant>& data, QObject* parent)
    : QAbstractItemModel(parent)
{
    QVector<QVariant> rootData;
    for (const QString& header : headers)
        rootData << header;

    rootItem = new TreeItem(rootData);
    setupModelData(data, rootItem);
}

TreeModel::~TreeModel()
{
    delete rootItem;
}

QVariant TreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();
    auto item = getItem(index);
    if (item == rootItem)
        return QVariant();
    return item->data(index.column());
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return QVariant();

    return rootItem->data(section);
}

TreeItem* TreeModel::getItem(const QModelIndex& index) const
{
    if (index.isValid()) {
        TreeItem* item = static_cast<TreeItem*>(index.internalPointer());
        if (item)
            return item;
    }
    return rootItem;
}

int TreeModel::rowCount(const QModelIndex& parent) const
{
    TreeItem* parentItem = getItem(parent);

    return parentItem->childCount();
}

int TreeModel::columnCount(const QModelIndex& /* parent */) const
{
    return rootItem->columnCount();
}

Qt::ItemFlags TreeModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return nullptr;

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

bool TreeModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    auto item = getItem(index);
    if (item == rootItem || role != Qt::EditRole)
        return false;
    if (item->setData(index.column(), value)) {
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

bool TreeModel::insertRows(int position, int rows, const QModelIndex& parent)
{
    if (rows < 1)
        return false;
    auto item = getItem(parent);
    if (position < 0 || position >= item->childCount())
        position = item->childCount();
    beginInsertRows(parent, position, position + rows - 1);
    bool success = item->insertChildren(position, rows, 0);
    endInsertRows();
    return success;
}

bool TreeModel::removeRows(int, int rows, const QModelIndex& current_index)
{
    if (!current_index.isValid() || rows < 1)
        return false;
    auto parent_index = parent(current_index);

    int position = current_index.row();

    auto parent_item = getItem(parent_index);
    if (position + rows > parent_item->childCount())
        rows = parent_item->childCount() - position;
    beginRemoveRows(parent_index, position, position + rows-1);
    bool success = parent_item->removeChildren(position, rows);
    endRemoveRows();
    return success;
}

bool TreeModel::insertLayers(int rows, const QModelIndex& current_selection)
{
    int position = current_selection.isValid() ? current_selection.row() + 1 : 0;
    QModelIndex parent = current_selection.isValid() ? current_selection.parent() : QModelIndex();

    if (!insertRows(position, rows, parent))
        return false;

    auto parent_item = getItem(parent);
    for(int i = position; i < position + rows; ++i)
        parent_item->child(i)->setData(defaultLayerData());

    emit dataChanged(index(position, 0, parent), index(position + rows - 1, columnCount(), parent));
    return true;
}

bool TreeModel::insertAssemblies(int rows, const QModelIndex& current_selection)
{
    int position = current_selection.isValid() ? current_selection.row() + 1 : 0;
    QModelIndex parent = current_selection.isValid() ? current_selection.parent() : QModelIndex();

    if (!insertRows(position, rows, parent))
        return false;

    auto parent_item = getItem(parent);
    for(int i = position; i < position + rows; ++i) {
        auto item = parent_item->child(i);
        item->setData(defaultAssemblyData());
        if (!insertRows(0, 1, index(position, 0, parent)))
            continue;
        item->child(0)->setData(defaultLayerData());
    }

    emit dataChanged(index(position, 0, parent), index(position + rows - 1, columnCount(), parent));
    return true;
}

void TreeModel::setupModelData(const QVector<QVariant>& data, TreeItem* parent)
{
    if (data.empty())
        return;
    parent->insertChildren(0, 1, data.size());
    auto child_item = parent->child(0);
    child_item->setData(data);
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex& parent) const
{
    TreeItem* parentItem = getItem(parent);

    TreeItem* childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex& index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem* childItem = getItem(index);
    TreeItem* parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->childNumber(), 0, parentItem);
}
