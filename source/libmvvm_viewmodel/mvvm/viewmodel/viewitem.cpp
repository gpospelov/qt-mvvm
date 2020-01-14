// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/model/customvariants.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/viewmodel/viewitem.h>
#include <mvvm/viewmodel/viewmodelutils.h>

using namespace ModelView;

ViewItem::ViewItem(SessionItem* item, int item_role) : m_item(item), m_item_role(item_role) {}

//! Returns data from underlying SessionItem.

ViewItem::~ViewItem() = default;

QVariant ViewItem::data(int role) const
{
    if (!m_item)
        return QStandardItem::data(role);

    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return Utils::toQtVariant(m_item->data(m_item_role));
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
    else if (role == Qt::ForegroundRole)
#else
    else if (role == Qt::TextColorRole)
#endif
        return Utils::TextColorRole(*m_item);
    else
        return QStandardItem::data(role);
}

void ViewItem::setData(const QVariant& value, int role)
{
    if (m_item && role == Qt::EditRole)
        m_item->setData(Utils::toCustomVariant(value), m_item_role);
    else
        QStandardItem::setData(value, role);
}

SessionItem* ViewItem::item()
{
    return m_item;
}

ViewItem* ViewItem::clone() const
{
    throw std::runtime_error("ViewItem::clone() -> Error. Attempt to call clone.");
}

//! Returns SessionItem role tracked by this ViewItem.

int ViewItem::item_role() const
{
    return m_item_role;
}
