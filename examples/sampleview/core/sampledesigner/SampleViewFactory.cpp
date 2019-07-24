// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "SampleViewFactory.h"
#include "LayerView.h"
#include "MultiLayerView.h"
#include "item_constants.h"

namespace {
    const QList<std::string> m_valid_item_names = { Constants::MultiLayerType, Constants::LayerType };
}

bool SampleViewFactory::isValidType(const std::string& name)
{
    return m_valid_item_names.contains(name);
}


IView* SampleViewFactory::createSampleView(const std::string& name)
{
    if (name == Constants::MultiLayerType)
        return new MultiLayerView();
    else if (name == Constants::LayerType)
        return new LayerView();
    return nullptr;
}
