// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <datarowstrategy.h>

#include <mvvm/model/sessionitem.h>
#include <mvvm/viewmodel/standardviewitems.h>

using namespace ModelView;

QStringList DataRowStrategy::horizontalHeaderLabels() const
{
    return QStringList() << "Name"
                         << "Information";
}

std::vector<std::unique_ptr<ViewItem>> DataRowStrategy::constructRefRow(SessionItem* item)
{
    std::vector<std::unique_ptr<ViewItem>> result;

    if (!item)
        return result;

    result.emplace_back(std::make_unique<ViewLabelItem>(item));
    if (item->hasData())
        result.emplace_back(std::make_unique<ViewDataItem>(item));
    else
        result.emplace_back(std::make_unique<ViewEmptyItem>());
    return result;
}
