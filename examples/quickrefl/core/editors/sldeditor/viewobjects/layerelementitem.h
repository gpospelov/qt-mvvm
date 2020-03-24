// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef LAYERELEMENTITEM_H
#define LAYERELEMENTITEM_H

#include <mvvm/model/compounditem.h>
#include <mvvm/model/sessionmodel.h>

class LayerElementItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_X_POS = "P_X_POS";
    static inline const std::string P_WIDTH = "P_WIDTH";
    static inline const std::string P_HEIGHT = "P_HEIGHT";

    static inline const std::string P_SIDE_THICKNESS = "P_SIDE_THICKNESS";
    static inline const std::string P_SIDE_BRUSH_COLOR = "P_SIDE_BRUSH_COLOR";
    static inline const std::string P_SIDE_PEN_WIDTH = "P_SIDE_PEN_WIDTH";
    static inline const std::string P_SIDE_PEN_COLOR = "P_SIDE_PEN_COLOR";

    static inline const std::string P_TOP_THICKNESS = "P_TOP_THICKNESS";
    static inline const std::string P_TOP_BRUSH_COLOR = "P_TOP_BRUSH_COLOR";
    static inline const std::string P_TOP_PEN_WIDTH = "P_TOP_PEN_WIDTH";
    static inline const std::string P_TOP_PEN_COLOR = "P_TOP_PEN_COLOR";

    LayerElementItem();
};

#endif
