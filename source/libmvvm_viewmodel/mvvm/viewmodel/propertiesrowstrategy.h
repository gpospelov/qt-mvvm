// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_PROPERTIESROWSTRATEGY_H
#define MVVM_VIEWMODEL_PROPERTIESROWSTRATEGY_H

#include <mvvm/viewmodel/rowstrategyinterface.h>

class QStandardItem;

namespace ModelView
{

class SessionItem;

//! Constructs row of QStandardItem's for given SessionItem.
//! Row consists of columns with all PropertyItem's of given SessionItem.

class CORE_EXPORT PropertiesRowStrategy : public RowStrategyInterface
{
public:
    PropertiesRowStrategy(const std::vector<std::string>& labels);

    QList<QStandardItem*> constructRow(SessionItem* item);
    QStringList horizontalHeaderLabels() const;

private:
    std::vector<std::string> m_column_labels;
};

} // namespace ModelView

#endif  // MVVM_VIEWMODEL_PROPERTIESROWSTRATEGY_H
