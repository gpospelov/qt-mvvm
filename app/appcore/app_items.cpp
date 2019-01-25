// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "app_items.h"
#include "taginfo.h"
#include "itemmanager.h"
#include <stdexcept>

using namespace AppItems;
using namespace ModelView;

const std::string MultiLayer::T_LAYERS = "layer tag";

MultiLayer::MultiLayer()
    : SessionItem(MultiLayerType)
{
    registerTag(TagInfo::universalTag(T_LAYERS, {LayerType}), /*set_as_default*/true);
}

Layer::Layer()
    : SessionItem(LayerType)
{

}

SessionItem* ItemFactory::createItem(const model_type& modelType)
{
    SessionItem* result(nullptr);

    if (modelType == MultiLayerType)
        result = new MultiLayer;

    else if (modelType == LayerType)
        result = new Layer;

    if (!result)
        throw std::runtime_error("ItemFactory::createItem() -> Error. Unknown model '"+
                                 modelType+"'");

    result->setDisplayName(modelType);
    return result;
}

SessionItem* ItemFactory::createEmptyItem()
{
    return new SessionItem;
}

SampleModel::SampleModel()
    : SessionModel("AppModel")
{
    m_item_manager->setItemFactory(std::make_unique<ItemFactory>());
}
