// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/model/sessionitem.h>
#include <mvvm/viewmodel/labeldatarowstrategy.h>
#include <mvvm/viewmodel/standardviewitems.h>

using namespace ModelView;

//! Example:
//! For LayerItem two items will be generated: ViewLabelItem and ViewEmptyItem, both uneditable.
//! For LayerItem's thickness property, two items will be generated: ViewLabelItem and ViewDataItem.

QStringList LabelDataRowStrategy::horizontalHeaderLabels() const
{
    return QStringList() << "Name"
                         << "Value";
}

std::vector<std::unique_ptr<ViewItem>> LabelDataRowStrategy::constructRefRow(SessionItem* item)
{
    std::vector<std::unique_ptr<ViewItem>> result;

    if (!item)
        return result;

    result.emplace_back(std::make_unique<ViewLabelItem>(item));
    if (item->data<QVariant>().isValid()) // FIXME cleanup
        result.emplace_back(std::make_unique<ViewDataItem>(item));
    else
        result.emplace_back(std::make_unique<ViewEmptyItem>());
    return result;
}
