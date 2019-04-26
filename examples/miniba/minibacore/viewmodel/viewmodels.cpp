// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "viewmodels.h"
#include "MaterialTableModel.h"


std::unique_ptr<ModelView::AbstractViewModel> Utils::CreateMaterialTableModel(ModelView::SessionModel* model)
{
    return std::make_unique<MaterialTableModel>(model);
}
