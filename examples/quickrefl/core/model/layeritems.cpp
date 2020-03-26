// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "layeritems.h"
#include "item_constants.h"
#include "materialitems.h"
#include "materialmodel.h"
#include <QVariant>
#include <mvvm/model/externalproperty.h>
#include <mvvm/signals/itemmapper.h>

RoughnessItem::RoughnessItem() : ModelView::CompoundItem(::Constants::RoughnessItemType)
{
    addProperty(P_SIGMA, 0.0)->setDisplayName("Sigma");
    addProperty(P_HURST, 0.5)->setDisplayName("Hurst");
    addProperty(P_LATERAL_CORR_LENGTH, 0.0)->setDisplayName("Correlation length");
}

//! ---------------------------------------------------------------------------

LayerItem::LayerItem() : ModelView::CompoundItem(::Constants::LayerItemType)
{
    addProperty(P_NAME, "Unnamed")->setDisplayName("Name");
    addProperty(P_MATERIAL, MaterialModel::undefined_material())->setDisplayName("Material");
    addProperty(P_THICKNESS, 0.0)->setDisplayName("Thickness");
    addProperty<RoughnessItem>(P_ROUGHNESS);
}

//! ---------------------------------------------------------------------------

MultiLayerItem::MultiLayerItem() : ModelView::CompoundItem(::Constants::MultiLayerItemType)
{
    addProperty(P_NAME, "Unnamed")->setDisplayName("Name");
    addProperty(P_NREPETITIONS, 1)->setDisplayName("Nr.");
    std::vector<std::string> allowed_child = {::Constants::MultiLayerItemType,
                                              ::Constants::LayerItemType};
    registerTag(ModelView::TagInfo::universalTag(T_LAYERS, allowed_child), /*set_default*/ true);

    void update_layer_appearance();
}

void MultiLayerItem::activate()
{
    auto on_item_inserted = [this](ModelView::SessionItem*, ModelView::TagRow) {
        update_layer_appearance();
    };
    mapper()->setOnItemInserted(on_item_inserted, this);

    auto on_item_removed = [this](ModelView::SessionItem*, ModelView::TagRow) {
        update_layer_appearance();
    };
    mapper()->setOnItemRemoved(on_item_removed, this);
}

//! Creates multi-slice presentation of internal layers structure. Used as simulation input.
//! TODO Provide unit tests, provide support for nested MultiLayers

multislice_t MultiLayerItem::multislice() const
{
    multislice_t result;
    auto layers = items<LayerItem>(T_LAYERS);
    for (const auto& layer : items<LayerItem>(T_LAYERS)) {
        if (layer->modelType() != Constants::LayerItemType)
            throw std::runtime_error("Currently supports layers only. FIXME");

        double thickness = layer->property(LayerItem::P_THICKNESS).value<double>();
        auto roughness = layer->item<RoughnessItem>(LayerItem::P_ROUGHNESS);
        double sigma = roughness->property(RoughnessItem::P_SIGMA).value<double>();

        auto material = model()->findItem(layer->property(LayerItem::P_MATERIAL)
                                              .value<ModelView::ExternalProperty>()
                                              .identifier());
        double sld_real = material->property(SLDMaterialItem::P_SLD_REAL).value<double>();
        double sld_imag = material->property(SLDMaterialItem::P_SLD_IMAG).value<double>();

        result.push_back({complex_t{sld_real, sld_imag}, thickness, sigma});
    }

    return result;
}

//! Sets thickness property of top and bottom layers to disabled state.
//! Reset thickness of top and bottom layer to 0.

void MultiLayerItem::update_layer_appearance()
{
    auto layers = items<LayerItem>(T_LAYERS);
    for (auto it = layers.begin(); it != layers.end(); ++it) {
        if (it == layers.begin() || std::next(it) == layers.end()) {
            (*it)->getItem(LayerItem::P_THICKNESS)->setEnabled(false);
            (*it)->setProperty(LayerItem::P_THICKNESS, 0.0);
        } else {
            (*it)->getItem(LayerItem::P_THICKNESS)->setEnabled(true);
        }
    }
}
