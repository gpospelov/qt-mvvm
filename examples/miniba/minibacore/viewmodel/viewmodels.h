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

#include "mvvm_global.h"
#include "abstractviewmodel.h"
#include <memory>

namespace Utils
{

CORE_EXPORT std::unique_ptr<ModelView::AbstractViewModel> CreateMaterialTableModel(ModelView::SessionModel* model);

} // Utils


#endif

