// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "editorbuilders.h"
#include "scientificdoubleeditor.h"
#include "sessionitem.h"
#include "reallimits.h"
#include "customvariants.h"
#include "combopropertyeditor.h"
#include "booleditor.h"
#include "coloreditor.h"
#include "externalpropertyeditor.h"
#include "scientificspinboxeditor.h"
#include <QDoubleSpinBox>

namespace {
double getStep(double val)
{
    return val == 0.0 ? 1.0 : val / 100.;
}
}

namespace ModelView {
namespace EditorBuilders {

builder_t BoolEditorBuilder()
{
    auto builder = [](const SessionItem*) -> std::unique_ptr<CustomEditor> {
        return std::make_unique<BoolEditor>();
    };
    return builder;
}

builder_t ScientificDoubleEditorBuilder()
{
    auto builder = [](const SessionItem* item) -> std::unique_ptr<CustomEditor> {
        auto editor = std::make_unique<ScientificDoubleEditor>();
        auto variant = item->data(ItemDataRole::LIMITS);
        if (variant.isValid()) {
            auto limits = variant.value<RealLimits>();
            editor->setRange(limits.lowerLimit(), limits.upperLimit());
        }
        return std::move(editor);
    };
    return builder;
}

builder_t ScientificSpinBoxEditorBuilder()
{
    auto builder = [](const SessionItem* item) -> std::unique_ptr<CustomEditor> {
        auto editor = std::make_unique<ScientificSpinBoxEditor>();
        auto limits = item->data(ItemDataRole::LIMITS);
        if (limits.isValid())
            editor->setLimits(limits.value<RealLimits>());
        editor->setSingleStep(getStep(item->data(ItemDataRole::DATA).toDouble()));
        editor->setDecimals(2);
        return std::move(editor);
    };
    return builder;
}

builder_t ColorEditorBuilder()
{
    auto builder = [](const SessionItem*) -> std::unique_ptr<CustomEditor> {
        return std::make_unique<ColorEditor>();
    };
    return builder;
}

builder_t ComboPropertyEditorBuilder()
{
    auto builder = [](const SessionItem*) -> std::unique_ptr<CustomEditor> {
        return std::make_unique<ComboPropertyEditor>();
    };
    return builder;
}

builder_t ExternalPropertyEditorBuilder()
{
    auto builder = [](const SessionItem*) -> std::unique_ptr<CustomEditor> {
        return std::make_unique<ExternalPropertyEditor>();
    };
    return builder;
}


} // namespace EditorBuilders
} // namespace ModelView
