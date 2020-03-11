// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "SegmentItem.h"
#include <QColor>
#include <QUndoStack>
#include <cmath>
#include <mvvm/core/modeldocuments.h>
#include <mvvm/model/itemcatalogue.h>
#include <mvvm/utils/numericutils.h>
#include <mvvm/utils/reallimits.h>

SegmentItem::SegmentItem(std::string layer_identifier_in) 
    : ModelView::CompoundItem("SegmentItem"), layer_identifier(layer_identifier_in)

{
    addProperty(P_COLOR, QColor(Qt::red))->setDisplayName("Color");
    addProperty(P_X_POS, 10.)->setLimits(ModelView::RealLimits::limitless())->setDisplayName("X");
    addProperty(P_Y_POS, 10.)->setLimits(ModelView::RealLimits::limitless())->setDisplayName("Y");
    addProperty(P_HEIGHT, 5.0)
        ->setLimits(ModelView::RealLimits::limitless())
        ->setDisplayName("Height");
    addProperty(P_WIDTH, 5.)
        ->setLimits(ModelView::RealLimits::limitless())
        ->setDisplayName("Width");
    addProperty(P_HORIZONTAL, true)
        ->setLimits(ModelView::RealLimits::limitless())
        ->setDisplayName("Horizontal");
}

void SegmentItem::setLayerIdentifier(std::string layer_identifier_in)
{
    layer_identifier = layer_identifier_in;
}

std::string SegmentItem::layerIdentifier(std::string layer_identifier_in)
{
    return layer_identifier;
}
