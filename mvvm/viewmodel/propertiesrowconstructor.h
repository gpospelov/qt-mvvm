// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_PROPERTIESROWCONSTRUCTOR_H
#define MVVM_PROPERTIESROWCONSTRUCTOR_H

#include "rowstrategyinterface.h"

class QStandardItem;

namespace ModelView
{

class SessionItem;

//! Constructs row of QStandardItem's for given SessionItem.
//! Row consists of columns with all PropertyItem's of given SessionItem.

class CORE_EXPORT PropertiesRowConstructor : public RowStrategyInterface
{
public:
    PropertiesRowConstructor(const std::vector<std::string>& labels);

    QList<QStandardItem*> constructRow(SessionItem* item);
    int columnCount() const;
    QStringList horizontalHeaderLabels() const;

private:
    std::vector<std::string> m_column_labels;
};

} // namespace ModelView

#endif // MVVM_PROPERTIESROWCONSTRUCTOR_H
