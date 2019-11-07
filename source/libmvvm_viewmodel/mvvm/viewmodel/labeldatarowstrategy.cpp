// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/viewmodel/labeldatarowstrategy.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/viewmodel/viewitems.h>

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
    if (item->data().isValid())
        result.push_back(new ViewDataItem(item));
    else
        result.push_back(new ViewEmptyItem);
    return result;
}

QStringList LabelDataRowStrategy::horizontalHeaderLabels() const
{
    return QStringList() << "Name" << "Value";
}
