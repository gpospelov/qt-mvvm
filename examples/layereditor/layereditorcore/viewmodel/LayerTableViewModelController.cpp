// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "LayerTableViewModelController.h"
#include "standardchildrenstrategies.h"
#include "labeldatarowstrategy.h"

using namespace ModelView;

LayerTableViewModelController::LayerTableViewModelController(AbstractViewModel* view_model)
    : AbstractViewModelController(view_model)
{
    setRowStrategy(std::make_unique<LabelDataRowStrategy>());
    setChildrenStrategy(std::make_unique<AllChildrenStrategy>());
}
