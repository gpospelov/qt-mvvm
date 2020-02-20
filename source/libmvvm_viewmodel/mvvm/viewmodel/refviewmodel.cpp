// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/viewmodel/refviewitem.h>
#include <mvvm/viewmodel/refviewmodel.h>

using namespace ModelView;

struct RefViewModel::RefViewModelImpl {
    RefViewModel* model{nullptr};
    std::unique_ptr<RefViewItem> root;
    RefViewModelImpl(RefViewModel* model) : model(model) {}

    bool item_belongs_to_model(RefViewItem* item)
    {
        return model->indexFromItem(item).isValid() || item == model->rootItem();
    }
};

RefViewModel::RefViewModel(QObject* parent)
    : QAbstractItemModel(parent), p_impl(std::make_unique<RefViewModelImpl>(this))
{
    p_impl->root = std::unique_ptr<RefViewItem>(new RefViewItem(nullptr, 0));
}

RefViewModel::~RefViewModel() = default;

QModelIndex RefViewModel::index(int row, int column, const QModelIndex& parent) const
{
    auto parent_item = itemFromIndex(parent) ? itemFromIndex(parent) : rootItem();
    const bool is_valid_row = row >= 0 && row < rowCount(parent);
    const bool is_valid_column = column >= 0 && column < columnCount(parent);
    return is_valid_row && is_valid_column
               ? createIndex(row, column, parent_item->child(row, column))
               : QModelIndex();
}

QModelIndex RefViewModel::parent(const QModelIndex& child) const
{
    if (auto child_item = itemFromIndex(child); child_item) {
        auto parent_item = child_item->parent();
        return parent_item == rootItem()
                   ? QModelIndex()
                   : createIndex(parent_item->row(), parent_item->column(), parent_item);
    }

    return QModelIndex();
}

int RefViewModel::rowCount(const QModelIndex& parent) const
{
    auto parent_item = itemFromIndex(parent);
    return parent_item ? parent_item->rowCount() : rootItem()->rowCount();
}

int RefViewModel::columnCount(const QModelIndex& parent) const
{
    auto parent_item = itemFromIndex(parent);
    return parent_item ? parent_item->columnCount() : rootItem()->columnCount();
}

QVariant RefViewModel::data(const QModelIndex& index, int role) const
{
    if (!rootItem())
        return QVariant();

    auto item = itemFromIndex(index);
    return item ? item->data(role) : QVariant();
}

bool RefViewModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid())
        return false;

    if (auto item = itemFromIndex(index); item) {
        bool result = item->setData(value, role);
        if (result)
            dataChanged(index, index, QVector<int>() << role);
        return result;
    }

    return false;
}

//! Returns a pointer to invisible root item.

RefViewItem* RefViewModel::rootItem() const
{
    return p_impl->root.get();
}

//! Returns a pointer to the RefViewItem associated with the given index.
//! If index is invalid, returns nullptr.

RefViewItem* RefViewModel::itemFromIndex(const QModelIndex& index) const
{
    return index.isValid() ? static_cast<RefViewItem*>(index.internalPointer()) : nullptr;
}

//! Returns the QModelIndex associated with the given item.

QModelIndex RefViewModel::indexFromItem(const RefViewItem* item) const
{
    return item && item->parent()
               ? createIndex(item->row(), item->column(), const_cast<RefViewItem*>(item))
               : QModelIndex();
}

void RefViewModel::removeRow(RefViewItem* parent, int row)
{
    if (!p_impl->item_belongs_to_model(parent))
        throw std::runtime_error("Error in RefViewModel: attempt to use parent from another model");

    beginRemoveRows(indexFromItem(parent), row, row);
    parent->removeRow(row);
    endRemoveRows();
}

//! Insert a row of items at index 'row' to given parent.

void RefViewModel::insertRow(RefViewItem* parent, int row,
                             std::vector<std::unique_ptr<RefViewItem>> items)
{
    if (!p_impl->item_belongs_to_model(parent))
        throw std::runtime_error("Error in RefViewModel: attempt to use parent from another model");

    beginInsertRows(indexFromItem(parent), row, row);
    parent->appendRow(std::move(items));
    endInsertRows();
}

//! Appends row of items to given parent.

void RefViewModel::appendRow(RefViewItem* parent, std::vector<std::unique_ptr<RefViewItem>> items)
{
    insertRow(parent, parent->rowCount(), std::move(items));
}

//! Returns the item flags for the given index.

Qt::ItemFlags RefViewModel::flags(const QModelIndex& index) const
{
    Qt::ItemFlags result = QAbstractItemModel::flags(index);
    if (auto item = itemFromIndex(index); item)
        result |= item->flags();
    return result;
}
