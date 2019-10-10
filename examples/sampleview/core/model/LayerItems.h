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

/*!
@file LayerItems.h
@brief Collection of layer and multi-layer items to populate SampleModel.
*/

#include "LocatedItem.h"

/*!
@class LayerItem
@brief Layer with name, thickness and reference to material.
*/

// TODO: disentangle from LocatedItem
class LayerItem : public LocatedItem
{
public:
    static const std::string P_NAME;
    static const std::string P_MATERIAL;
    static const std::string P_THICKNESS;
    static const std::string T_LAYOUTS;
    LayerItem();
};

/*!
@class MultiLayerItem
@brief Multi layer capable of holding layers and other multi-layers.
*/

// TODO: disentangle from LocatedItem
class MultiLayerItem : public LocatedItem
{
public:
    static const std::string T_LAYERS;
    static const std::string P_NREPETITIONS;
    MultiLayerItem();
};

#endif // LAYERITEM_H
