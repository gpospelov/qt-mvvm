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
#include "itemmapper.h"
#include "customvariants.h"
#include <QDebug>

using namespace ModelView;

ViewItem::ViewItem(SessionItem* item, int item_role)
    : m_item(item), m_item_role(item_role)
{
}

//! Returns data from underlying SessionItem.

ViewItem::~ViewItem()
{
}

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

    if (role == Qt::EditRole) {
        qDebug() << "ViewItem::setData";
        m_item->setData(toCustomVariant(value), m_item_role);
        qDebug() << "!!! setting data";
    }

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
