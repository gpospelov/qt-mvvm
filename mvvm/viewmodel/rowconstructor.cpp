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
    const int fixed_column_count(2);
    return fixed_column_count;
}
