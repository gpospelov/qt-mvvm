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
#include <QDoubleSpinBox>

namespace ModelView {
namespace EditorBuilders {

//strategy_t DefaultDoubleEditorConstructor()
//{
//    auto creator = [](const SessionItem* item) -> std::unique_ptr<CustomEditor> {
//        auto editor = std::make_unique<QDoubleSpinBox>();
//        auto limits = item->data(ItemDataRole::LIMITS);
//        if (limits.isValid()) {
//            auto real_limits = limits.value<RealLimits>();
//            editor->setRange(real_limits.lowerLimit(), real_limits.upperLimit());
//        }
//        return std::move(editor);
//    };
//    return creator;
//}

builder_t ScientificDoubleEditorBuilder()
{
    auto builder = [](const SessionItem* item) -> std::unique_ptr<CustomEditor> {
        auto editor = std::make_unique<ScientificDoubleEditor>();
        auto limits = item->data(ItemDataRole::LIMITS);
        if (limits.isValid())
            editor->setLimits(limits.value<RealLimits>());
        return std::move(editor);
    };
    return builder;
}

}
}
