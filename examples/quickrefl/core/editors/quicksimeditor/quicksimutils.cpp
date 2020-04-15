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

namespace
{

//! Creates slice from layer content.
Slice create_slice(const ModelView::SessionItem& layer)
{
    if (layer.modelType() != Constants::LayerItemType)
        throw std::runtime_error("Error in create_slice(): not a layer.");

    double thickness = layer.property<double>(LayerItem::P_THICKNESS);
    auto roughness = layer.item<RoughnessItem>(LayerItem::P_ROUGHNESS);
    double sigma = roughness->property<double>(RoughnessItem::P_SIGMA);

    auto material_property = layer.property<ModelView::ExternalProperty>(LayerItem::P_MATERIAL);
    auto material = layer.model()->findItem(material_property.identifier());
    // layer which is not linked with material will get (0,0) as SLD material.
    double sld_real = material ? material->property<double>(SLDMaterialItem::P_SLD_REAL) : 0.0;
    double sld_imag = material ? material->property<double>(SLDMaterialItem::P_SLD_IMAG) : 0.0;
    return {complex_t{sld_real, sld_imag}, thickness, sigma};
}

//! Adds slices to existing vector of slices using content of a multilayer.
//! Will be called recursively for multilayers inside multilayers.
void AddToMultiSlice(multislice_t& result, const ModelView::SessionItem& multilayer)
{
    for (const auto item : multilayer.getItems(MultiLayerItem::T_LAYERS)) {
        if (item->modelType() == Constants::LayerItemType) {
            result.push_back(create_slice(*item));
        } else if (item->modelType() == Constants::MultiLayerItemType) {
            const int rep_count = item->property<int>(MultiLayerItem::P_NREPETITIONS);
            for (int i_rep = 0; i_rep < rep_count; ++i_rep)
                AddToMultiSlice(result, *item);
        } else {
            throw std::runtime_error("Error in AddToMultiSlice: unsupported item type.");
        }
    }
}

} // namespace

multislice_t Utils::CreateMultiSlice(const MultiLayerItem& multilayer)
{
    multislice_t result;
    AddToMultiSlice(result, multilayer);
    return result;
}
