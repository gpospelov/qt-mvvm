// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "standarditemcatalogue.h"
#include "mvvm_types.h"
#include "vectoritem.h"
#include "propertyitem.h"
#include "compounditem.h"
#include "linkeditem.h"
#include "axesitems.h"
#include "data1ditem.h"
#include "graphitem.h"

using namespace ModelView;

std::unique_ptr<ItemCatalogue> ModelView::CreateStandardItemCatalogue()
{
    auto result = std::make_unique<ItemCatalogue>();
    result->registerItem<SessionItem>();
    result->registerItem<PropertyItem>();
    result->registerItem<CompoundItem>();
    result->registerItem<VectorItem>();
    result->registerItem<LinkedItem>();
    result->registerItem<FixedBinAxisItem>();
    result->registerItem<Data1DItem>();
    result->registerItem<GraphItem>();
    return result;
}
