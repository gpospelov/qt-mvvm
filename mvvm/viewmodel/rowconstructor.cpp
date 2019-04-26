// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "rowconstructor.h"
#include "sessionitem.h"
#include "viewitems.h"

using namespace ModelView;

//! Example:
//! For LayerItem two items will be generated: ViewLabelItem and ViewEmptyItem, both uneditable.
//! For LayerItem's thickness property, two items will be generated: ViewLabelItem and ViewDataItem.

QList<QStandardItem*> DefaultRowConstructor::constructRow(SessionItem* item)
{
    QList<QStandardItem*> result;

    if (!item)
        return result;

    result.push_back(new ViewLabelItem(item));
    if (item->data(ItemDataRole::DATA).isValid())
        result.push_back(new ViewDataItem(item));
    else
        result.push_back(new ViewEmptyItem);
    return result;
}

int DefaultRowConstructor::columnCount() const
{
    const int fixed_number_of_row_elements(2);
    return fixed_number_of_row_elements;
}
