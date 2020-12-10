// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SAMPLEMODEL_H
#define SAMPLEMODEL_H

#include <mvvm/model/compounditem.h>
#include <mvvm/model/sessionmodel.h>

//! Layer with name, thickness and reference to material.

class LayerItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_NAME = "P_NAME";
    static inline const std::string P_MATERIAL = "P_MATERIAL";
    static inline const std::string P_THICKNESS = "P_THICKNESS";
    LayerItem();
};

//! Multi layer capable of holding layers and other multi-layers.

class MultiLayerItem : public ModelView::CompoundItem
{
public:
    static inline const std::string T_LAYERS = "T_LAYERS";
    static inline const std::string P_NREPETITIONS = "P_NREPETITIONS";
    MultiLayerItem();
};

//! Model to hold layers and multi-layers.

class SampleModel : public ModelView::SessionModel
{
public:
    SampleModel();

private:
    void init_model();
};

#endif //  SAMPLEMODEL_H
