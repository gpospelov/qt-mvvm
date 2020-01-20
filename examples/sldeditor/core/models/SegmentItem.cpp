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
    addProperty(P_X_INI, -20.)->setLimits(ModelView::RealLimits::limitless())->setDisplayName("X start");
    addProperty(P_Y_INI, 0.0)->setLimits(ModelView::RealLimits::limitless())->setDisplayName("Y start");
    addProperty(P_X_FIN, 20.)->setLimits(ModelView::RealLimits::limitless())->setDisplayName("X end");
    addProperty(P_Y_FIN, 0.0)->setLimits(ModelView::RealLimits::limitless())->setDisplayName("Y end");
}