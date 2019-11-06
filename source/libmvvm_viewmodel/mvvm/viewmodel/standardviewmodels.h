// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_STANDARDVIEWMODELS_H
#define MVVM_STANDARDVIEWMODELS_H

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

} // Utils

} // ModelView

#endif // MVVM_STANDARDVIEWMODELS_H
