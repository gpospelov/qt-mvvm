// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef ROUGHNESSITEM_H
#define ROUGHNESSITEM_H

#include <mvvm/model/compounditem.h>
#include <mvvm/model/sessionmodel.h>

class SampleModel;
class MaterialModel;

/*!
@class RoughnessItem
@brief Domain object to hold mouse info.
*/
class RoughnessViewItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_ROUGHNESS = "P_ROUGHNESS";
    static inline const std::string P_COLOR = "P_COLOR";
    RoughnessViewItem();

    void setLayerIdentifier(std::string layer_identifier_in);
    std::string layerIdentifier();
    void fetchFromLayer(SampleModel* layer_model, MaterialModel* material_model);
    
private:
    std::string layer_identifier;
};

#endif // ROUGHNESSITEM_H
