// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "viewitems.h"
#include "model_types.h"
#include "sessionitem.h"
#include "customvariants.h"

using namespace ModelView;

namespace {
const int empty_item_type = QStandardItem::UserType+1;
const int label_item_type = QStandardItem::UserType+2;
const int data_item_type = QStandardItem::UserType+3;
}

ViewEmptyItem::ViewEmptyItem()
    : ViewItem(nullptr, ItemDataRole::DISPLAY)
{
    setEditable(false);
}

int ViewEmptyItem::type() const
{
    return empty_item_type;
}

QVariant ViewEmptyItem::data(int role) const
{
    return QStandardItem::data(role);
}

ViewEmptyItem* ViewEmptyItem::clone() const
{
    return new ViewEmptyItem;
}

// ----------------------------------------------------------------------------

ViewLabelItem::ViewLabelItem(SessionItem* item)
    : ViewItem(item, ItemDataRole::DISPLAY)
{
    setEditable(false);
}

int ViewLabelItem::type() const
{
    return label_item_type;
}

QVariant ViewLabelItem::data(int role) const
{
    if (!m_item)
        return QStandardItem::data(role);

    // use item's display role
    if (role == Qt::DisplayRole || role == Qt::EditRole)
        return QString::fromStdString(m_item->displayName());

    return QStandardItem::data(role);
}

// ----------------------------------------------------------------------------

ViewDataItem::ViewDataItem(SessionItem* item)
    : ViewItem(item, ItemDataRole::DATA)
{
}

int ViewDataItem::type() const
{
    return data_item_type;
}
