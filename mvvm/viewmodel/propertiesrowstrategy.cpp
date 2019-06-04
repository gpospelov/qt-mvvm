// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "propertiesrowstrategy.h"
#include "itemutils.h"
#include "sessionitem.h"
#include "viewitems.h"

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
        if (child->data(ItemDataRole::DATA).isValid())
            result.push_back(new ViewDataItem(child));
        else
            result.push_back(new ViewEmptyItem);
    }
    return result;
}

int PropertiesRowStrategy::columnCount() const
{
    return static_cast<int>(m_column_labels.size());
}

QStringList PropertiesRowStrategy::horizontalHeaderLabels() const
{
    QStringList result;
    std::transform(m_column_labels.begin(), m_column_labels.end(), std::back_inserter(result),
                   [](const std::string& str) { return QString::fromStdString(str); });
    return result;
}
