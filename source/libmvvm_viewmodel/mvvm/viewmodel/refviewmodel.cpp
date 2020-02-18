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
    std::unique_ptr<RefViewItem> root;
    RefViewModelImpl() : root(std::make_unique<RefViewItem>()) {}
};

RefViewModel::RefViewModel(QObject* parent)
    : QAbstractItemModel(parent), p_impl(std::make_unique<RefViewModelImpl>())
{
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
    Q_UNUSED(child)
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
    Q_UNUSED(index)
    Q_UNUSED(role)
    return QVariant();
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

void RefViewModel::appendRow(const QModelIndex& parent,
                             std::vector<std::unique_ptr<RefViewItem>> items)
{
    auto parent_item = itemFromIndex(parent) ? itemFromIndex(parent) : rootItem();
    beginInsertRows(parent, parent_item->rowCount(), parent_item->rowCount());
    parent_item->appendRow(std::move(items));
    endInsertRows();
}
