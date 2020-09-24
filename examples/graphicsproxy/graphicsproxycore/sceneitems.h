// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef GRAPHICSPROXY_SCENEITEMS_H
#define GRAPHICSPROXY_SCENEITEMS_H

//! @file sceneitems.h
//! Collection of items for graphics scene.

#include <mvvm/model/compounditem.h>

//! Item to represent region of interest on top of heat map.

class RegionOfInterestItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_XLOW = "P_XLOW";
    static inline const std::string P_YLOW = "P_YLOW";
    static inline const std::string P_XUP = "P_XUP";
    static inline const std::string P_YUP = "P_YUP";

    RegionOfInterestItem();
};

#endif // GRAPHICSPROXY_SCENEMODEL_H
