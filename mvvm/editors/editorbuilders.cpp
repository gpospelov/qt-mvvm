// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "editorbuilders.h"
#include "booleditor.h"
#include "coloreditor.h"
#include "combopropertyeditor.h"
#include "customvariants.h"
#include "externalpropertyeditor.h"
#include "reallimits.h"
#include "scientificdoubleeditor.h"
#include "scientificspinboxeditor.h"
#include "sessionitem.h"
#include "integereditor.h"
#include <QDoubleSpinBox>
#include <cmath>

namespace
{
double getStep(double val)
{
    return val == 0.0 ? 1.0 : val / 100.;
}

// double singleStep(int decimals) {
//    // For item with decimals=3 (i.e. 0.001) single step will be 0.1
//    return 1. / std::pow(10., decimals - 1);
//}

} // namespace

namespace ModelView
{
namespace EditorBuilders
{

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
        auto variant = item->data(ItemDataRole::LIMITS);
        if (variant.isValid()) {
            auto limits = variant.value<RealLimits>();
            editor->setRange(limits.lowerLimit(), limits.upperLimit());
        }
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

builder_t IntegerEditorBuilder()
{
    auto builder = [](const SessionItem* item) -> std::unique_ptr<CustomEditor> {
        auto editor = std::make_unique<IntegerEditor>();
        auto variant = item->data(ItemDataRole::LIMITS);
        if (variant.isValid()) {
            auto limits = variant.value<RealLimits>();
            editor->setRange(static_cast<int>(limits.lowerLimit()),
                             static_cast<int>(limits.upperLimit()));
        }
        return std::move(editor);
    };
    return builder;
}

} // namespace EditorBuilders
} // namespace ModelView
