// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/viewmodel/refviewitem.h>
#include <vector>

using namespace ModelView;

struct RefViewItem::RefViewItemImpl {
    std::vector<std::unique_ptr<RefViewItem>> children;
    int rows{0};
    int columns{0};
    SessionItem* item;
    int role;
    RefViewItemImpl(SessionItem* item, int role) : item(item), role(role) {}

    void appendRow(std::vector<std::unique_ptr<RefViewItem>> items)
    {
        if (items.empty())
            throw std::runtime_error("Error in RefViewItem: attempt to append empty row");

        if (columns > 0 && items.size() != static_cast<size_t>(columns))
            throw std::runtime_error("Error in RefViewItem: wrong number of columns.");

        children.insert(children.end(), std::make_move_iterator(items.begin()),
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
};

RefViewItem::RefViewItem(SessionItem* item, int role)
    : p_impl(std::make_unique<RefViewItemImpl>(item, role))
{
}

RefViewItem::~RefViewItem() = default;

int RefViewItem::rowCount() const
{
    return p_impl->rows;
}

int RefViewItem::columnCount() const
{
    return p_impl->columns;
}

void RefViewItem::appendRow(std::vector<std::unique_ptr<RefViewItem>> items)
{
    p_impl->appendRow(std::move(items));
}

void RefViewItem::clear()
{
    p_impl->children.clear();
    p_impl->rows = 0;
    p_impl->columns = 0;
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
