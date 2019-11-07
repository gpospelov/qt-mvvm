// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/viewmodel/propertiesrowstrategy.h>
#include <mvvm/model/itemutils.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/viewmodel/viewitems.h>

using namespace ModelView;

PropertiesRowStrategy::PropertiesRowStrategy(const std::vector<std::string>& labels)
    : m_column_labels(labels)
{
}

QList<QStandardItem*> PropertiesRowStrategy::constructRow(SessionItem* item)
{
    QList<QStandardItem*> result;

    if (!item)
        return result;

    for (auto child : Utils::SinglePropertyItems(*item)) {
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
    std::transform(m_column_labels.begin(), m_column_labels.end(), std::back_inserter(result),
                   [](const std::string& str) { return QString::fromStdString(str); });
    return result;
}
