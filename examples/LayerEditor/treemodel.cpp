#include "treemodel.h"
#include <QSize>

namespace
{
const QVector<QVariant> header_data{"Name", "Material", "Thickness", "Roughness"};
const int n_cols = 4;
} // namespace

TreeModel::TreeModel(TreeItem* root_item, QObject* parent)
    : QAbstractItemModel(parent)
    , rootItem(root_item)
{}

TreeModel::TreeModel(QObject* parent) : QAbstractItemModel(parent), rootItem(new AssemblyItem())
{
    rootItem->insertChildren(0, 1, TreeItem::Layer);
}

TreeModel::~TreeModel()
{
    delete rootItem;
}

QVariant TreeModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::UserRole)
        return getItem(index)->type();
    if (role == Qt::DisplayRole)
        return getItem(index)->data(index.column());
    return QVariant();
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
        return QVariant();

    if (section < 0 || section >= n_cols)
        return QVariant();

    return header_data[section];
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

void TreeModel::insertDefaultLayerIntoAssembly(const QModelIndex& current_selection)
{
    if (!current_selection.isValid())
        return;

    int position = 0;
    auto item = getItem(current_selection);
    beginInsertRows(current_selection, position, position);
    item->insertChildren(position, 1, TreeItem::Layer);
    endInsertRows();
}

int TreeModel::rowCount(const QModelIndex& parent) const
{
    TreeItem* parentItem = getItem(parent);

    return parentItem->childCount();
}

int TreeModel::columnCount(const QModelIndex& /* parent */) const
{
    return n_cols;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return 0;

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
    throw std::runtime_error("Error in TreeModel::insertRows: method should not be called.");
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
    beginRemoveRows(parent_index, position, position + rows - 1);
    bool success = parent_item->removeChildren(position, rows);
    endRemoveRows();
    return success;
}

QSize TreeModel::span(const QModelIndex& index) const
{
    auto item = getItem(index);
    if (item->type() == TreeItem::Assembly && index.column() == 0)
        return QSize(columnCount(), 1);
    return QAbstractItemModel::span(index);
}

bool TreeModel::insertLayers(int rows, const QModelIndex& current_selection)
{
    if (rows < 1)
        return false;

    int position = current_selection.isValid() ? current_selection.row() + 1 : 0;
    QModelIndex parent = current_selection.isValid() ? current_selection.parent() : QModelIndex();

    auto item = getItem(parent);
    if (position > item->childCount())
        position = item->childCount();
    beginInsertRows(parent, position, position + rows - 1);
    bool success = item->insertChildren(position, rows, TreeItem::Layer);
    endInsertRows();

    return success;
}

bool TreeModel::insertAssemblies(int rows, const QModelIndex& current_selection)
{
    if (rows < 1)
        return false;

    int position = current_selection.isValid() ? current_selection.row() + 1 : 0;
    QModelIndex parent = current_selection.isValid() ? current_selection.parent() : QModelIndex();

    auto item = getItem(parent);
    if (position > item->childCount())
        position = item->childCount();
    beginInsertRows(parent, position, position + rows - 1);
    bool success = item->insertChildren(position, rows, TreeItem::Assembly);
    endInsertRows();

    //for (int i = position; i < position + rows; ++i)
    //     insertDefaultLayerIntoAssembly(index(position, 0, parent));

    return success;
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
