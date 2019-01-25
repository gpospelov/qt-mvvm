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

using namespace ModelView;

namespace {
const int label_item_type = QStandardItem::UserType+1;
const int data_item_type = QStandardItem::UserType+2;
}

ViewLabelItem::ViewLabelItem(SessionItem* item)
    : ViewItem(item, ItemDataRole::DISPLAY)
{
    setEditable(false);
}

int ViewLabelItem::type() const
{
    return label_item_type;
}

ViewDataItem::ViewDataItem(SessionItem* item)
    : ViewItem(item, ItemDataRole::DATA)
{
}

int ViewDataItem::type() const
{
    return data_item_type;
}
