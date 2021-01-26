// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "samplemodel.h"
#include "sampleitems.h"
#include "mvvm/utils/numericutils.h"
#include "mvvm/widgets/widgetutils.h"
#include <QColor>

namespace DragAndMove {

namespace {
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
} // namespace

SampleModel::SampleModel() : SessionModel("SampleModel")
{
    registerItem<DemoItem>();
    registerItem<DemoContainerItem>();
    populateModel();
    setUndoRedoEnabled(true);
}

void SampleModel::appendRandomItem(ModelView::SessionItem* container)
{
    auto item = insertItem<DemoItem>(container);
    item->setProperty(DemoItem::P_COLOR_PROPERTY, ModelView::Utils::RandomColor());
    item->setProperty(DemoItem::P_STRING_PROPERTY, random_name());
    item->setProperty(DemoItem::P_INTEGER_PROPERTY, ModelView::Utils::RandInt(0, 10));
}

//! Generates initial model content.

void SampleModel::populateModel()
{
    auto container = insertItem<DemoContainerItem>();
    appendRandomItem(container);
    appendRandomItem(container);
    appendRandomItem(container);

    container = insertItem<DemoContainerItem>();
    appendRandomItem(container);
    appendRandomItem(container);
}

} // namespace DragAndMove
