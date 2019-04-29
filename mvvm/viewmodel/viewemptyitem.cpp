// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "viewemptyitem.h"
#include "viewitemtypes.h"
#include "mvvm_types.h"
#include "viewmodelutils.h"

using namespace ModelView;

ViewEmptyItem::ViewEmptyItem() : ViewItem(nullptr, ItemDataRole::DISPLAY)
{
    setEditable(false);
}

int ViewEmptyItem::type() const
{
    return ViewItemTypes::empty_item_type;
}

QVariant ViewEmptyItem::data(int role) const
{
    return QStandardItem::data(role);
}

ViewEmptyItem* ViewEmptyItem::clone() const
{
    return new ViewEmptyItem;
}
