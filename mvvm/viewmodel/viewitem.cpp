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

using namespace ModelView;

ViewItem::ViewItem(SessionItem* item)
   : m_item(item)
{

}

//! Returns data from underlying SessionItem.

QVariant ViewItem::data(int role) const
{
    if (!m_item)
        return QVariant();

    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        return m_item->data(ItemDataRole::DATA);
    }

    return QVariant();
}

void ViewItem::setData(const QVariant& value, int role)
{
    if (!m_item)
        return;

    if (role == Qt::EditRole)
        m_item->setData(value, ItemDataRole::DATA);
}

SessionItem* ViewItem::item()
{
    return m_item;
}
