// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_STANDARDVIEWMODELS_H
#define MVVM_VIEWMODEL_STANDARDVIEWMODELS_H

#include <memory>
#include <mvvm_viewmodel_export.h>
#include <mvvm/viewmodel/viewmodel.h>

namespace ModelView
{

class SessionModel;
class ViewModel;

namespace Utils
{

//! Creates view model to represent SessionModel for Qt views.
//! The model has two columns, all items are shown.
MVVM_VIEWMODEL_EXPORT std::unique_ptr<ViewModel> CreateDefaultViewModel(SessionModel* model);

//! Creates view model to represent SessionModel for Qt views.
//! The model has two columns, shows only property items and simplified group items.
MVVM_VIEWMODEL_EXPORT std::unique_ptr<ViewModel> CreatePropertyViewModel(SessionModel* model);

//! Creates view model to represent SessionModel for Qt views.
//! Shows all properties of CompoundItem in columns of the table, rows of the table represent
//! different CompoundItems. Items of same type and table like structure of the model are expected.
MVVM_VIEWMODEL_EXPORT std::unique_ptr<ViewModel> CreatePropertyTableViewModel(SessionModel* model);

//! Creates view model to represent SessionModel for Qt views.
//! Shows only top items.
MVVM_VIEWMODEL_EXPORT std::unique_ptr<ViewModel> CreateTopItemsViewModel(SessionModel* model);

//! Creates view model to represent SessionModel for Qt views.
//! The model has two columns, shows only property items and simplified group items.
//! Subproperties of group item moved one level up.
MVVM_VIEWMODEL_EXPORT std::unique_ptr<ViewModel> CreatePropertyFlatViewModel(SessionModel* model);

} // namespace Utils

} // namespace ModelView

#endif // MVVM_VIEWMODEL_STANDARDVIEWMODELS_H
