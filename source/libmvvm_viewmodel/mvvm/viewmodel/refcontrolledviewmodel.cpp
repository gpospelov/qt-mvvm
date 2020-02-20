// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/viewmodel/refcontrolledviewmodel.h>
#include <mvvm/viewmodel/refviewmodelcontroller.h>

using namespace ModelView;

RefControlledViewModel::RefControlledViewModel(std::unique_ptr<RefViewModelController> controller,
                                               QObject* parent)
{
}

RefControlledViewModel::~RefControlledViewModel() = default;
