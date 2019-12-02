// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mousemodel.h"
#include <QColor>
#include <mvvm/model/itemcatalogue.h>

static const int MouseCount = 7;

MouseItem::MouseItem() : ModelView::CompoundItem("MouseItem")
{
    addProperty(P_ANGLE, 0.0)->setDisplayName("Angle");
    addProperty(P_SPEED, 0.0)->setDisplayName("Speed");
    addProperty(P_EYE_DIRECTION, 0.0)->setDisplayName("Eye direction");
    addProperty(P_COLOR, QColor(Qt::red))->setDisplayName("Color");
}

MouseModel::MouseModel() : ModelView::SessionModel("MouseModel")
{
    auto catalogue = std::make_unique<ModelView::ItemCatalogue>();
    catalogue->registerItem<MouseItem>();
    setItemCatalogue(std::move(catalogue));

    create_mice();
}

void MouseModel::create_mice()
{
    for (int i = 0; i < MouseCount; ++i)
        insertItem<MouseItem>();
}
