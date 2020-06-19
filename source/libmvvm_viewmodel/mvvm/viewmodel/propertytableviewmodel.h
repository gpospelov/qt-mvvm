// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_PROPERTYTABLEVIEWMODEL_H
#define MVVM_VIEWMODEL_PROPERTYTABLEVIEWMODEL_H

#include <mvvm/viewmodel/viewmodel.h>

namespace ModelView
{

/*!
@class PropertyTableViewModel
@brief View model to show content of SessionModel in Qt widgets: all item properties as a table row.

Given view model is intended to show registered properties of items in table-like view.
Registered properties will form columns of the table, top level items will form table rows.
*/

class CORE_EXPORT PropertyTableViewModel : public ViewModel
{
    Q_OBJECT
public:
    PropertyTableViewModel(SessionModel* model, QObject* parent = nullptr);
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_PROPERTYTABLEVIEWMODEL_H
