// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "samplemodel.h"
#include "item_constants.h"
#include "itemcatalogue.h"
#include "items.h"
#include "numericutils.h"
#include <QColor>

namespace
{
std::unique_ptr<ModelView::ItemCatalogue> CreateToyItemCatalogue()
{
    std::unique_ptr<ModelView::ItemCatalogue> result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<DemoItem>();
    result->registerItem<DemoContainerItem>();
    return result;
}

QColor random_color()
{
    auto rndm = []() -> int { return ModelView::Utils::RandInt(0, 255); };
    return QColor(rndm(), rndm(), rndm());
}

std::string random_name()
{
    static const std::string alphabet = "abcdefgh";
    const size_t len(3);

    std::string result;
    for (size_t i = 0; i < len; ++i) {
        size_t random_index =
            static_cast<size_t>(ModelView::Utils::RandInt(0, static_cast<int>(alphabet.size() - 1)));
        result.push_back(alphabet[random_index]);
    }

    return result;
}
} // namespace

SampleModel::SampleModel() : SessionModel("SampleModel")
{
    setItemCatalogue(CreateToyItemCatalogue());
    init_model_content();
    setUndoRedoEnabled(true);
}

void SampleModel::append_random_item(ModelView::SessionItem* container)
{
    auto item = insertItem<DemoItem>(container);
    item->setProperty(DemoItem::P_COLOR_PROPERTY, random_color());
    item->setProperty(DemoItem::P_STRING_PROPERTY, QVariant::fromValue(random_name()));
    item->setProperty(DemoItem::P_INTEGER_PROPERTY, ModelView::Utils::RandInt(0, 10));
}

//! Generates initial model content.

void SampleModel::init_model_content()
{
    auto container = insertItem<DemoContainerItem>();
    append_random_item(container);
    append_random_item(container);
    append_random_item(container);

    container = insertItem<DemoContainerItem>();
    append_random_item(container);
    append_random_item(container);
}
