// ************************************************************************** //
//                                                                              
//  Model-view-view-model framework for large GUI applications                  
//                                                                              
//! @authors   see AUTHORS                                                      
//! @license   GNU General Public License v3 or higher (see COPYING)            
//                                                                              
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_LABELDATAROWSTRATEGY_H
#define MVVM_VIEWMODEL_LABELDATAROWSTRATEGY_H

#include <mvvm/viewmodel/rowstrategyinterface.h>

class QStandardItem;

namespace ModelView
{

class SessionItem;

//! Constructs row of QStandardItem's for given SessionItem.
//! Row consists of two columns, ViewLabelItem for SessionItem's display role and
//! ViewDataItem for Session's item data role.

class CORE_EXPORT LabelDataRowStrategy : public RowStrategyInterface
{
public:
    QList<QStandardItem*> constructRow(SessionItem* item);
    QStringList horizontalHeaderLabels() const;
};

} // namespace ModelView

#endif  // MVVM_VIEWMODEL_LABELDATAROWSTRATEGY_H
