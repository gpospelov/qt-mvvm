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
#include <QRandomGenerator>
#include <mvvm/model/itemcatalogue.h>
#include <mvvm/utils/numericutils.h>
#include <cmath>

namespace {
static const int MouseCount = 7;

std::unique_ptr<ModelView::ItemCatalogue> CreateItemCatalogue()
{
    auto result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<MouseItem>();
    return result;
}

QColor random_color()
{
    auto rndm = []() -> int { return ModelView::Utils::RandInt(0, 255); };
    return QColor(rndm(), rndm(), rndm());
}


}

MouseItem::MouseItem() : ModelView::CompoundItem("MouseItem")
{
    addProperty(P_COLOR, QColor(Qt::red))->setDisplayName("Color");
    addProperty(P_XPOS, 0.0)->setDisplayName("X");
    addProperty(P_YPOS, 0.0)->setDisplayName("Y");
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
        item->setProperty(MouseItem::P_XPOS, std::sin((i * 6.28) / MouseCount) * 200);
        item->setProperty(MouseItem::P_YPOS, std::cos((i * 6.28) / MouseCount) * 200);
        item->setProperty(MouseItem::P_COLOR, QVariant::fromValue(random_color()));
    }
}
