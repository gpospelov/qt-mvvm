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
#include <cmath>

namespace {
static const int MouseCount = 7;

std::unique_ptr<ModelView::ItemCatalogue> CreateItemCatalogue()
{
    auto result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<MouseItem>();
    return result;
}

}

MouseItem::MouseItem() : ModelView::CompoundItem("MouseItem")
{
    addProperty(P_ANGLE, 0.0)->setDisplayName("Angle");
    addProperty(P_SPEED, 0.0)->setDisplayName("Speed");
    addProperty(P_EYE_DIRECTION, 0.0)->setDisplayName("Eye direction");
    addProperty(P_COLOR, QColor(Qt::red))->setDisplayName("Color");
    addProperty(P_POSX, 0.0)->setDisplayName("X");
    addProperty(P_POSY, 0.0)->setDisplayName("Y");
}

MouseModel::MouseModel() : ModelView::SessionModel("MouseModel")
{
    setItemCatalogue(CreateItemCatalogue());
    populate_model();
}

void MouseModel::populate_model()
{
    for (int i = 0; i < MouseCount; ++i) {
        auto item = insertItem<MouseItem>();
        item->setProperty(MouseItem::P_POSX, std::sin((i * 6.28) / MouseCount) * 200);
        item->setProperty(MouseItem::P_POSY, std::cos((i * 6.28) / MouseCount) * 200);
    }
}
