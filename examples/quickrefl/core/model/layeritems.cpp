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

//! Sets thickness property of top and bottom layers to disabled state.
//! Reset thickness of top and bottom layer to 0.

void MultiLayerItem::update_layer_appearance()
{
    // FIXME restore correct enabling/disabling of thickness and roughness of top and bottom layers
    // FIXME together with tests in layeritems.test.cpp
    if (parent() != model()->rootItem())
        return;
        
    auto layers = items<LayerItem>(T_LAYERS);
    for (auto it = layers.begin(); it != layers.end(); ++it) {
        if (it == layers.begin()) {
            (*it)->getItem(LayerItem::P_THICKNESS)->setEnabled(false);
            (*it)->getItem(LayerItem::P_ROUGHNESS)->getItem(RoughnessItem::P_SIGMA)->setEnabled(false);
            (*it)->setProperty(LayerItem::P_THICKNESS, 0.0);
        } else if(std::next(it) == layers.end()) {
            (*it)->getItem(LayerItem::P_THICKNESS)->setEnabled(false);
            (*it)->setProperty(LayerItem::P_THICKNESS, 0.0);
        } else {
            (*it)->getItem(LayerItem::P_THICKNESS)->setEnabled(true);
        }
    }
}
