// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "graphmodel.h"
#include "mvvm_types.h"

using namespace ModelView;

GraphModel::GraphModel() : SessionModel("GraphModel")
{
    init_model();
}

void GraphModel::init_model()
{
    insertNewItem(Constants::Data1DItemType);
}
