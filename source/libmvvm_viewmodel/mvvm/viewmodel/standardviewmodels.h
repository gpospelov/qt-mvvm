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

#include <mvvm/core/export.h>
#include <memory>

namespace ModelView
{

class SessionModel;
class AbstractViewModel;

namespace Utils
{

//! Creates view model to represent SessionModel for Qt views.
//! The model has two columns, all items are shown.
CORE_EXPORT std::unique_ptr<AbstractViewModel> CreateDefaultViewModel(SessionModel* model);

//! Creates view model to represent SessionModel for Qt views.
//! The model has two columns, shows only property items and simplified group items.
CORE_EXPORT std::unique_ptr<AbstractViewModel> CreatePropertyViewModel(SessionModel* model);

//! Creates view model to represent SessionModel for Qt views.
//! Shows only top items.
CORE_EXPORT std::unique_ptr<AbstractViewModel> CreateTopItemsViewModel(SessionModel* model);

//! Creates view model to represent SessionModel for Qt views.
//! The model has two columns, shows only property items and simplified group items.
//! Subproperties of group item moved one level up.
CORE_EXPORT std::unique_ptr<AbstractViewModel> CreatePropertyFlatViewModel(SessionModel* model);

} // Utils

} // ModelView

#endif  // MVVM_VIEWMODEL_STANDARDVIEWMODELS_H
