// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "labeldatarowstrategy.h"
#include "sessionitem.h"
#include "viewitems.h"

namespace  {
const int fixed_number_of_row_elements(2);
}

using namespace ModelView;

//! Example:
//! For LayerItem two items will be generated: ViewLabelItem and ViewEmptyItem, both uneditable.
//! For LayerItem's thickness property, two items will be generated: ViewLabelItem and ViewDataItem.

QList<QStandardItem*> LabelDataRowStrategy::constructRow(SessionItem* item)
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

int LabelDataRowStrategy::columnCount() const
{
    return fixed_number_of_row_elements;
}

QStringList LabelDataRowStrategy::horizontalHeaderLabels() const
{
    return QStringList() << "Name" << "Value";
}
