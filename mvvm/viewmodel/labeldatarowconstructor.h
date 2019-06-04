// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_LABELDATAROWCONSTRUCTOR_H
#define MVVM_LABELDATAROWCONSTRUCTOR_H

#include "rowstrategyinterface.h"

class QStandardItem;

namespace ModelView
{

class SessionItem;

//! Constructs row of QStandardItem's for given SessionItem.
//! Row consists of two columns, ViewLabelItem for SessionItem's display role and
//! ViewDataItem for Session's item data role.

class CORE_EXPORT LabelDataRowConstructor : public RowStrategyInterface
{
public:
    QList<QStandardItem*> constructRow(SessionItem* item);
    int columnCount() const;
    QStringList horizontalHeaderLabels() const;
};

} // namespace ModelView

#endif // MVVM_LABELDATAROWCONSTRUCTOR_H
