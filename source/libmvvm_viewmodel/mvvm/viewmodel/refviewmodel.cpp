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
    auto parent_item = itemForIndex(parent);
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
    return itemForIndex(parent)->rowCount();
}

int RefViewModel::columnCount(const QModelIndex& parent) const
{
    return itemForIndex(parent)->columnCount();
}

QVariant RefViewModel::data(const QModelIndex& index, int role) const
{
    Q_UNUSED(index)
    Q_UNUSED(role)
    return QVariant();
}

RefViewItem* RefViewModel::rootItem() const
{
    return p_impl->root.get();
}

RefViewItem* RefViewModel::itemForIndex(const QModelIndex& index) const
{
    return index.isValid() ? static_cast<RefViewItem*>(index.internalPointer())
                           : p_impl->root.get();
}

void RefViewModel::appendRow(RefViewItem* parent, std::vector<std::unique_ptr<RefViewItem>> items)
{
    parent->appendRow(std::move(items));
}
