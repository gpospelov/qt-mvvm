// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef LAYERITEMS_H
#define LAYERITEMS_H

#include "compounditem.h"

//! @file LayerItems.h
//! Collection of layer and multi-layer items to populate SampleModel.

//! Layer with name, thickness and reference to material.

class CORE_EXPORT LayerItem : public ModelView::CompoundItem
{
public:
    static const std::string P_NAME;
    static const std::string P_MATERIAL;
    static const std::string P_THICKNESS;
    LayerItem();
};

//! Multi layer capable of holding layers and other multi-layers.

class CORE_EXPORT MultiLayerItem : public ModelView::CompoundItem
{
public:
    static const std::string T_LAYERS;
    static const std::string P_NREPETITIONS;
    MultiLayerItem();
};

#endif // LAYERITEM_H
