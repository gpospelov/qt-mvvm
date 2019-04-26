// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "viewitems.h"
#include "mvvm_types.h"
#include "sessionitem.h"
#include "customvariants.h"
#include "viewmodelutils.h"

using namespace ModelView;

namespace {
const int empty_item_type = QStandardItem::UserType+1;
const int label_item_type = QStandardItem::UserType+2;
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
    setEditable(false); // label view is always read only
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

    return ViewItem::data(role);
}

