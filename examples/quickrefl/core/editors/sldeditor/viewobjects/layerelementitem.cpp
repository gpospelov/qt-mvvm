// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "layerelementitem.h"

#include <mvvm/core/modeldocuments.h>
#include <mvvm/model/externalproperty.h>
#include <mvvm/model/itemcatalogue.h>
#include <mvvm/utils/numericutils.h>
#include <mvvm/utils/reallimits.h>

LayerElementItem::LayerElementItem() : ModelView::CompoundItem("LayerElement")
{
    addProperty(P_X_POS, 0.)->setDisplayName("Position");
    addProperty(P_WIDTH, 10.)->setDisplayName("Width");
    addProperty(P_HEIGHT, 10.)->setDisplayName("Height");

    addProperty(P_SIDE_THICKNESS, 5.)->setDisplayName("Side segment thickness");
    addProperty(P_SIDE_BRUSH_COLOR, QColor("black"))->setDisplayName("Side segment color");
    addProperty(P_SIDE_PEN_WIDTH, 2.)->setDisplayName("Side segment pen width");
    addProperty(P_SIDE_PEN_COLOR, QColor("black"))->setDisplayName("Side segment pen color");

    addProperty(P_TOP_THICKNESS, 5.)->setDisplayName("Top segment thickness");
    addProperty(P_TOP_BRUSH_COLOR, QColor("black"))->setDisplayName("Top segment color");
    addProperty(P_TOP_PEN_WIDTH, 2.)->setDisplayName("Top segment pen width");
    addProperty(P_TOP_PEN_COLOR, QColor("black"))->setDisplayName("Top segment pen color");

    addProperty(P_HANDLE_RADIUS, 5.)->setDisplayName("Handle radius");
    addProperty(P_HANDLE_BRUSH_COLOR, QColor("black"))->setDisplayName("Handle color");
    addProperty(P_HANDLE_PEN_WIDTH, 2.)->setDisplayName("Handle pen width");
    addProperty(P_HANDLE_PEN_COLOR, QColor("black"))->setDisplayName("Handle pen color");
}