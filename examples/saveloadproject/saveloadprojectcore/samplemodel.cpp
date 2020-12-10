// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "samplemodel.h"
#include <QColor>
#include <mvvm/model/itemcatalogue.h>
#include <mvvm/model/sessionitemcontainer.h>
#include <mvvm/standarditems/containeritem.h>
#include <mvvm/utils/numericutils.h>
#include <mvvm/widgets/widgetutils.h>

namespace
{
std::unique_ptr<ModelView::ItemCatalogue> CreateItemCatalogue()
{
    auto result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<DemoItem>();
    return result;
}

std::string random_name()
{
    static const std::string alphabet = "abcdefgh";
    const size_t len(3);

    std::string result;
    for (size_t i = 0; i < len; ++i) {
        size_t random_index = static_cast<size_t>(
            ModelView::Utils::RandInt(0, static_cast<int>(alphabet.size() - 1)));
        result.push_back(alphabet[random_index]);
    }

    return result;
}

const std::string DemoItemType = "DemoItem";

} // namespace

using namespace ModelView;

DemoItem::DemoItem() : CompoundItem(DemoItemType)
{
    addProperty(P_COLOR_PROPERTY, QColor(Qt::green))->setDisplayName("Color");
    addProperty(P_BOOL_PROPERTY, true)->setDisplayName("Bool");
    addProperty(P_INTEGER_PROPERTY, 42)->setDisplayName("Integer");
    addProperty(P_STRING_PROPERTY, "abc")->setDisplayName("String");
    addProperty(P_DOUBLE_PROPERTY, 42.1)->setDisplayName("Double");
}

SampleModel::SampleModel() : SessionModel("SampleModel")
{
    setItemCatalogue(CreateItemCatalogue());
    initModelContent();
    setUndoRedoEnabled(true);
}

void SampleModel::appendNewItem(ModelView::SessionItem* container)
{
    auto item = insertItem<DemoItem>(container);
    item->setProperty(DemoItem::P_COLOR_PROPERTY, ModelView::Utils::RandomColor());
    item->setProperty(DemoItem::P_STRING_PROPERTY, random_name());
    item->setProperty(DemoItem::P_INTEGER_PROPERTY, ModelView::Utils::RandInt(0, 10));
}

//! Generates initial model content.

void SampleModel::initModelContent()
{
    auto container = insertItem<ModelView::ContainerItem>();
    appendNewItem(container);
    appendNewItem(container);
    appendNewItem(container);
}
