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

SegmentItem::SegmentItem() : ModelView::CompoundItem("SegmentItem")
{
    addProperty(P_COLOR, QColor(Qt::red))->setDisplayName("Color");
    addProperty(P_X_POS, -20.)->setLimits(ModelView::RealLimits::limitless())->setDisplayName("X");
    addProperty(P_Y_POS, -20.)->setLimits(ModelView::RealLimits::limitless())->setDisplayName("Y");
    addProperty(P_HEIGHT, 0.0)
        ->setLimits(ModelView::RealLimits::limitless())
        ->setDisplayName("Height");
    addProperty(P_WIDTH, 20.)
        ->setLimits(ModelView::RealLimits::limitless())
        ->setDisplayName("Width");
    addProperty(P_HORIZONTAL, true)
        ->setLimits(ModelView::RealLimits::limitless())
        ->setDisplayName("Horizontal");
}