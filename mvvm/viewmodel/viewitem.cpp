// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "viewitem.h"
#include "sessionitem.h"
#include "customvariants.h"

using namespace ModelView;

ViewItem::ViewItem(SessionItem* item, int item_role)
    : m_item(item), m_item_role(item_role)
{
}

//! Returns data from underlying SessionItem.

QVariant ViewItem::data(int role) const
{
    if (!m_item)
        return QStandardItem::data(role);

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        return toQtVariant(m_item->data(m_item_role));
    }

    return QStandardItem::data(role);
}

void ViewItem::setData(const QVariant& value, int role)
{
    if (!m_item) {
        QStandardItem::setData(value, role);
        return;
    }

    if (role == Qt::EditRole)
        m_item->setData(toCustomVariant(value), m_item_role);

    QStandardItem::setData(value, role);
}

SessionItem* ViewItem::item()
{
    return m_item;
}
