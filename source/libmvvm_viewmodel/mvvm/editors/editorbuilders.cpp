// ************************************************************************** //
//                                                                              
//  Model-view-view-model framework for large GUI applications                  
//                                                                              
//! @authors   see AUTHORS                                                      
//! @license   GNU General Public License v3 or higher (see COPYING)            
//                                                                              
// ************************************************************************** //

#include <mvvm/editors/editorbuilders.h>
#include <mvvm/editors/booleditor.h>
#include <mvvm/editors/doubleeditor.h>
#include <mvvm/editors/coloreditor.h>
#include <mvvm/editors/combopropertyeditor.h>
#include <mvvm/model/customvariants.h>
#include <mvvm/editors/externalpropertyeditor.h>
#include <mvvm/utils/reallimits.h>
#include <mvvm/editors/scientificdoubleeditor.h>
#include <mvvm/editors/scientificspinboxeditor.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/editors/integereditor.h>
#include <cmath>

namespace
{
const int default_decimals = 3;
double getStep(double val)
{
    return val == 0.0 ? 1.0 : val / 100.;
}

 double singleStep(int decimals) {
    // For item with decimals=3 (i.e. 0.001) single step will be 0.1
    return 1. / std::pow(10., decimals - 1);
}

} // namespace

namespace ModelView :: EditorBuilders
{

builder_t BoolEditorBuilder()
{
    auto builder = [](const SessionItem*) -> std::unique_ptr<CustomEditor> {
        return std::make_unique<BoolEditor>();
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

builder_t DoubleEditorBuilder()
{
    auto builder = [](const SessionItem* item) -> std::unique_ptr<CustomEditor> {
        auto editor = std::make_unique<DoubleEditor>();
        auto variant = item->data(ItemDataRole::LIMITS);
        if (variant.isValid()) {
            auto limits = variant.value<RealLimits>();
            editor->setRange(limits.lowerLimit(), limits.upperLimit());
            editor->setSingleStep(singleStep(default_decimals));
            editor->setDecimals(default_decimals);
        }
        return std::move(editor);
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
        editor->setSingleStep(getStep(item->data().value<double>()));
        editor->setDecimals(default_decimals);
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

} // namespace ModelView::EditorBuilders
