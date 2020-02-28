// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef LAYERITEMS_H
#define LAYERITEMS_H

//! @file layeritems.h
//! Collection of layer and multi-layer items to populate SampleModel.

#include <mvvm/model/compounditem.h>

//! Item to represent the roughness of the layer.

class RoughnessItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_SIGMA = "P_SIGMA";
    static inline const std::string P_HURST = "P_HURST";
    static inline const std::string P_LATERAL_CORR_LENGTH = "P_LATERAL_CORR_LENGTH";

    RoughnessItem();
};


//! Layer with name, thickness and reference to material.

class LayerItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_NAME = "P_NAME";
    static inline const std::string P_MATERIAL = "P_MATERIAL";
    static inline const std::string P_THICKNESS = "P_THICKNESS";
    static inline const std::string P_ROUGHNESS = "P_ROUGHNESS";

    LayerItem();
};

//! Multi layer capable of holding layers and other multi-layers.

class MultiLayerItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_NAME = "P_NAME";
    static inline const std::string T_LAYERS = "T_LAYERS";
    static inline const std::string P_NREPETITIONS = "P_NREPETITIONS";

    MultiLayerItem();

    void activate() override;

private:
    void update_layer_appearance();
};

#endif // LAYERITEM_H
