// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef VIEWMODELS_H
#define VIEWMODELS_H

#include "abstractviewmodel.h"
#include "mvvm_global.h"
#include <memory>

namespace Utils
{

//! Creates view model to represent content of MaterialModel in table like views.
CORE_EXPORT std::unique_ptr<ModelView::AbstractViewModel>
CreateMaterialTableModel(ModelView::SessionModel* model);

} // namespace Utils

#endif
