// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "AxisItem.h"
#include <QColor>
#include <QUndoStack>
#include <cmath>
#include <mvvm/core/modeldocuments.h>
#include <mvvm/model/itemcatalogue.h>
#include <mvvm/utils/numericutils.h>
#include <mvvm/utils/reallimits.h>


AxisItem::AxisItem() : ModelView::CompoundItem("AxisItem")
{
    addProperty(COLOR, QColor(Qt::red))->setDisplayName("Color");
    addProperty(THICKNESS, 10)->setDisplayName("Thickness");
    addProperty(OFFSET_X, 10)->setDisplayName("Offset x (%)");
    addProperty(OFFSET_Y, 10)->setDisplayName("Offset y (%)");
}