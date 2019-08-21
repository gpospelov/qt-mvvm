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
#include "data1ditem.h"
#include "graphitem.h"

using namespace ModelView;

GraphModel::GraphModel() : SessionModel("GraphModel")
{
    init_model();
}

void GraphModel::init_model()
{
    auto data = dynamic_cast<Data1DItem*>(insertNewItem(Constants::Data1DItemType));
    data->setFixedBinAxis(10, 0.0, 10.0);

    auto graph = dynamic_cast<GraphItem*>(insertNewItem(Constants::GraphItemType));

}
