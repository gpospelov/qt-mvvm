// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/model/itemutils.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/viewmodel/propertiesrowstrategy.h>
#include <mvvm/viewmodel/viewitems.h>

using namespace ModelView;

PropertiesRowStrategy::PropertiesRowStrategy(const std::vector<std::string>& labels)
    : user_defined_column_labels(labels)
{
}

QList<QStandardItem*> PropertiesRowStrategy::constructRow(SessionItem* item)
{
    QList<QStandardItem*> result;

    if (!item)
        return result;

    auto items_in_row = Utils::SinglePropertyItems(*item);
    if (user_defined_column_labels.empty())
        update_column_labels(items_in_row);

    for (auto child : items_in_row) {
        if (child->data().isValid())
            result.push_back(new ViewDataItem(child));
        else
            result.push_back(new ViewLabelItem(child));
    }
    return result;
}

QStringList PropertiesRowStrategy::horizontalHeaderLabels() const
{
    QStringList result;
    auto labels =
        user_defined_column_labels.empty() ? current_column_labels : user_defined_column_labels;
    std::transform(labels.begin(), labels.end(), std::back_inserter(result),
                   [](const std::string& str) { return QString::fromStdString(str); });
    return result;
}

//! Updates current column labels.

void PropertiesRowStrategy::update_column_labels(std::vector<SessionItem*> items)
{
    current_column_labels.clear();
    std::transform(items.begin(), items.end(), std::back_inserter(current_column_labels),
                   [](const SessionItem* item) { return item->displayName(); });
}
