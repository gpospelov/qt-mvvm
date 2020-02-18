// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <algorithm>
#include <mvvm/utils/containerutils.h>
#include <mvvm/viewmodel/refviewitem.h>
#include <vector>

using namespace ModelView;

struct RefViewItem::RefViewItemImpl {
    std::vector<std::unique_ptr<RefViewItem>> children; //! buffer to hold rows x columns
    int rows{0};
    int columns{0};
    SessionItem* item{nullptr};
    int role{0};
    RefViewItem* parent_view_item{nullptr};
    RefViewItemImpl(SessionItem* item, int role) : item(item), role(role) {}

    void appendRow(std::vector<std::unique_ptr<RefViewItem>> items)
    {
        insertRow(rows, std::move(items));
    }

    void insertRow(int row, std::vector<std::unique_ptr<RefViewItem>> items)
    {
        if (items.empty())
            throw std::runtime_error("Error in RefViewItem: attempt to insert empty row");

        if (columns > 0 && items.size() != static_cast<size_t>(columns))
            throw std::runtime_error("Error in RefViewItem: wrong number of columns.");

        if (row < 0 || row > rows)
            throw std::runtime_error("Error in RefViewItem: invalid row index.");

        children.insert(std::next(children.begin(), row*columns), std::make_move_iterator(items.begin()),
                        std::make_move_iterator(items.end()));

        columns = static_cast<int>(items.size());
        ++rows;
    }

    RefViewItem* child(int row, int column) const
    {
        if (row < 0 || row >= rows)
            throw std::runtime_error("Error in RefViewItem: wrong row)");

        if (column < 0 || column >= columns)
            throw std::runtime_error("Error in RefViewItem: wrong column)");

        return children.at(static_cast<size_t>(column + row * columns)).get();
    }

    RefViewItem* parent() { return parent_view_item; }

    int index_of_child(const RefViewItem* child)
    {
        return Utils::IndexOfItem(children.begin(), children.end(), child);
    }
};

RefViewItem::RefViewItem(SessionItem* item, int role)
    : p_impl(std::make_unique<RefViewItemImpl>(item, role))
{
}

RefViewItem::~RefViewItem() = default;

//! Returns the number of child item rows that the item has.

int RefViewItem::rowCount() const
{
    return p_impl->rows;
}

//! Returns the number of child item columns that the item has.

int RefViewItem::columnCount() const
{
    return p_impl->columns;
}

//! Appends a row containing items. Number of items should be the same as columnCount()
//! (if there are already some rows). If it is a first row, then items can be of any size.

void RefViewItem::appendRow(std::vector<std::unique_ptr<RefViewItem>> items)
{
    for (auto& x : items)
        x.get()->setParent(this);
    p_impl->appendRow(std::move(items));
}

//! Insert a row of items at index 'row'.

void RefViewItem::insertRow(int row, std::vector<std::unique_ptr<RefViewItem>> items)
{
    for (auto& x : items)
        x.get()->setParent(this);
    p_impl->insertRow(row, std::move(items));
}

void RefViewItem::clear()
{
    p_impl->children.clear();
    p_impl->rows = 0;
    p_impl->columns = 0;
}

RefViewItem* RefViewItem::parent() const
{
    return p_impl->parent();
}

RefViewItem* RefViewItem::child(int row, int column) const
{
    return p_impl->child(row, column);
}

SessionItem* RefViewItem::item() const
{
    return p_impl->item;
}

int RefViewItem::item_role() const
{
    return p_impl->role;
}

//! Returns the row where the item is located in its parent's child table, or -1 if the item has no
//! parent.

int RefViewItem::row() const
{
    auto index = parent() ? parent()->p_impl->index_of_child(this) : -1;
    return index >= 0 ? index / parent()->p_impl->columns : -1;
}

//! Returns the column where the item is located in its parent's child table, or -1 if the item has
//! no parent.

int RefViewItem::column() const
{
    auto index = parent() ? parent()->p_impl->index_of_child(this) : -1;
    return index >= 0 ? index % parent()->p_impl->columns : -1;
}

void RefViewItem::setParent(RefViewItem* parent)
{
    p_impl->parent_view_item = parent;
}
