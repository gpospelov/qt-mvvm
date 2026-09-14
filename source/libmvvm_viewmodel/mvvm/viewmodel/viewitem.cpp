// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/viewmodel/viewitem.h"
#include "mvvm/model/customvariants.h"
#include "mvvm/model/sessionitem.h"
#include "mvvm/utils/containerutils.h"
#include "mvvm/viewmodel/viewmodelutils.h"
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

using namespace ModelView;

struct ViewItem::ViewItemImpl {
    std::vector<std::unique_ptr<ViewItem>> m_children; //! buffer to hold m_rows x columns
    int m_rows{0};
    int m_columns{0};
    SessionItem* m_item{nullptr};
    int m_role{0};
    ViewItem* m_parent_view_item{nullptr};
    ViewItemImpl(SessionItem* item, int role) : m_item(item), m_role(role) {}

    void appendRow(std::vector<std::unique_ptr<ViewItem>> items)
    {
        insertRow(m_rows, std::move(items));
    }

    void insertRow(int row, std::vector<std::unique_ptr<ViewItem>> items)
    {
        if (items.empty())
            throw std::runtime_error("Error in ViewItemImpl: attempt to insert empty row");

        if (m_columns > 0 && items.size() != static_cast<size_t>(m_columns))
            throw std::runtime_error("Error in ViewItemImpl: wrong number of columns.");

        if (row < 0 || row > m_rows)
            throw std::runtime_error("Error in ViewItemImpl: invalid row index.");

        m_children.insert(std::next(m_children.begin(), row * m_columns),
                        std::make_move_iterator(items.begin()),
                        std::make_move_iterator(items.end()));

        m_columns = static_cast<int>(items.size());
        ++m_rows;
    }

    void removeRow(int row)
    {
        if (row < 0 || row >= m_rows)
            throw std::runtime_error("Error in RefViewItem: invalid row index.");

        auto begin = std::next(m_children.begin(), row * m_columns);
        auto end = std::next(begin, m_columns);
        m_children.erase(begin, end);
        --m_rows;
        if (m_rows == 0)
            m_columns = 0;
    }

    ViewItem* child(int row, int column) const
    {
        if (row < 0 || row >= m_rows)
            throw std::runtime_error("Error in RefViewItem: wrong row)");

        if (column < 0 || column >= m_columns)
            throw std::runtime_error("Error in RefViewItem: wrong column)");

        return m_children.at(static_cast<size_t>(column + row * m_columns)).get();
    }

    ViewItem* parent() { return m_parent_view_item; }

    int index_of_child(const ViewItem* child)
    {
        return Utils::IndexOfItem(m_children.begin(), m_children.end(), child);
    }

    //! Returns m_item data associated with this RefViewItem.

    QVariant data() const { return m_item ? m_item->data<QVariant>(m_role) : QVariant(); }

    //! Returns vector of m_children.

    std::vector<ViewItem*> get_children() const
    {
        std::vector<ViewItem*> result;
        std::transform(m_children.begin(), m_children.end(), std::back_inserter(result),
                       [](const auto& x) { return x.get(); });
        return result;
    }
};

ViewItem::ViewItem(SessionItem* item, int role) : p_impl(std::make_unique<ViewItemImpl>(item, role))
{
}

ViewItem::~ViewItem() = default;

//! Returns the number of child item m_rows that the item has.

int ViewItem::rowCount() const
{
    return p_impl->m_rows;
}

//! Returns the number of child item m_columns that the item has.

int ViewItem::columnCount() const
{
    return p_impl->m_columns;
}

//! Appends a row containing items. Number of items should be the same as columnCount()
//! (if there are already some rows). If it is a first row, then items can be of any size.

void ViewItem::appendRow(std::vector<std::unique_ptr<ViewItem>> items)
{
    for (auto& x : items)
        x->setParent(this);
    p_impl->appendRow(std::move(items));
}

//! Insert a row of items at index 'row'.

void ViewItem::insertRow(int row, std::vector<std::unique_ptr<ViewItem>> items)
{
    for (auto& x : items)
        x->setParent(this);
    p_impl->insertRow(row, std::move(items));
}

//! Removes row of items at given 'row'. Items will be deleted.

void ViewItem::removeRow(int row)
{
    p_impl->removeRow(row);
}

void ViewItem::clear()
{
    p_impl->m_children.clear();
    p_impl->m_rows = 0;
    p_impl->m_columns = 0;
}

ViewItem* ViewItem::parent() const
{
    return p_impl->parent();
}

ViewItem* ViewItem::child(int row, int column) const
{
    return p_impl->child(row, column);
}

SessionItem* ViewItem::item() const
{
    return p_impl->m_item;
}

int ViewItem::item_role() const
{
    return p_impl->m_role;
}

//! Returns the row where the item is located in its parent's child table, or -1 if the item has no
//! parent.

int ViewItem::row() const
{
    auto index = parent() ? parent()->p_impl->index_of_child(this) : -1;
    return index >= 0 ? index / parent()->p_impl->m_columns : -1;
}

//! Returns the column where the item is located in its parent's child table, or -1 if the item has
//! no parent.

int ViewItem::column() const
{
    auto index = parent() ? parent()->p_impl->index_of_child(this) : -1;
    return index >= 0 ? index % parent()->p_impl->m_columns : -1;
}

//! Returns the data for given role according to Qt::ItemDataRole namespace definitions.
//! Converts data and roles from underlying SessionItem to what Qt expects.

QVariant ViewItem::data(int qt_role) const
{
    if (!p_impl->m_item)
        return QVariant();

    if (qt_role == Qt::DisplayRole || qt_role == Qt::EditRole)
        return Utils::toQtVariant(p_impl->data());
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
    else if (qt_role == Qt::ForegroundRole)
#else
    else if (qt_role == Qt::TextColorRole)
#endif
        return Utils::TextColorRole(*p_impl->m_item);
    else if (qt_role == Qt::ToolTipRole)
        return Utils::ToolTipRole(*p_impl->m_item);
    else
        return QVariant();
}

//! Sets the data to underlying SessionItem.
//! Converts data and roles from Qt definitions to what SessionItem expects.

bool ViewItem::setData(const QVariant& value, int qt_role)
{
    if (p_impl->m_item && qt_role == Qt::EditRole)
        return p_impl->m_item->setData(Utils::toCustomVariant(value), p_impl->m_role);
    return false;
}

//! Returns Qt's item flags.
//! Converts internal SessionItem's status enable/disabled/readonly to what Qt expects.

Qt::ItemFlags ViewItem::flags() const
{
    Qt::ItemFlags result = Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    return result;
}

std::vector<ViewItem*> ViewItem::children() const
{
    return p_impl->get_children();
}

void ViewItem::setParent(ViewItem* parent)
{
    p_impl->m_parent_view_item = parent;
}
