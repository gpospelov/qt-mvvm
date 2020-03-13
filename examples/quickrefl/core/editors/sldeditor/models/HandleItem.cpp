// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "HandleItem.h"
#include <QColor>
#include <QUndoStack>
#include <cmath>
#include <mvvm/core/modeldocuments.h>
#include <mvvm/model/itemcatalogue.h>
#include <mvvm/utils/numericutils.h>
#include <mvvm/utils/reallimits.h>

HandleItem::HandleItem() : ModelView::CompoundItem("HandleItem")
{
    addProperty(P_COLOR, QColor(Qt::black))->setDisplayName("Color");
    addProperty(P_XPOS, 0.0)->setLimits(ModelView::RealLimits::limitless())->setDisplayName("X");
    addProperty(P_YPOS, 0.0)->setLimits(ModelView::RealLimits::limitless())->setDisplayName("Y");
    addProperty(P_RADIUS, 20.)
        ->setLimits(ModelView::RealLimits::limitless())
        ->setDisplayName("Radius");
}