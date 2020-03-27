// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "quicksimutils.h"
#include "item_constants.h"
#include "layeritems.h"
#include "materialitems.h"
#include <mvvm/model/externalproperty.h>
#include <mvvm/model/sessionmodel.h>

multislice_t Utils::CreateMultiSlice(const MultiLayerItem& multilayer)
{
    multislice_t result;
    for (const auto& layer : multilayer.items<LayerItem>(MultiLayerItem::T_LAYERS)) {
        if (layer->modelType() != Constants::LayerItemType)
            throw std::runtime_error("Currently supports layers only. FIXME");

        double thickness = layer->property(LayerItem::P_THICKNESS).value<double>();
        auto roughness = layer->item<RoughnessItem>(LayerItem::P_ROUGHNESS);
        double sigma = roughness->property(RoughnessItem::P_SIGMA).value<double>();

        auto material = multilayer.model()->findItem(layer->property(LayerItem::P_MATERIAL)
                                                         .value<ModelView::ExternalProperty>()
                                                         .identifier());
        double sld_real = material->property(SLDMaterialItem::P_SLD_REAL).value<double>();
        double sld_imag = material->property(SLDMaterialItem::P_SLD_IMAG).value<double>();

        result.push_back({complex_t{sld_real, sld_imag}, thickness, sigma});
    }

    return result;
}
