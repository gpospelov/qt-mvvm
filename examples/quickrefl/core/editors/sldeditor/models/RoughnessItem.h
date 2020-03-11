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

/*!
@class RoughnessItem
@brief Domain object to hold mouse info.
*/
class RoughnessItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_ROUGHNESS = "P_ROUGHNESS";
    static inline const std::string P_COLOR = "P_COLOR";
    RoughnessItem();

    void setLayerIdentifier(std::string layer_identifier_in);
    std::string layerIdentifier(std::string layer_identifier_in);

private:
    std::string layer_identifier;
};

#endif // ROUGHNESSITEM_H
