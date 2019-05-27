// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "defaulteditorfactory.h"
#include "customvariants.h"
#include "comboproperty.h"
#include "combopropertyeditor.h"
#include "sessionitem.h"
#include "viewitem.h"
#include "abstractviewmodel.h"
#include "booleditor.h"
#include "coloreditor.h"
#include "externalpropertyeditor.h"
#include "scientificdoubleeditor.h"
#include "scientificspinboxeditor.h"
#include "variant-constants.h"
#include "coloreditor.h"
#include <QDebug>
#include <QModelIndex>

using namespace ModelView;

namespace
{

const SessionItem* itemFromIndex(const QModelIndex& index)
{
    auto model = dynamic_cast<const AbstractViewModel*>(index.model());
    return model ? model->sessionItemFromIndex(index) : nullptr;
}

double getStep(double val)
{
    return val == 0.0 ? 1.0 : val / 100.;
}

} // namespace


DefaultEditorFactory::~DefaultEditorFactory() = default;

DefaultEditorFactory::DefaultEditorFactory()
{
    registerBuilder(Constants::bool_type_name, EditorBuilders::BoolEditorBuilder());
//    registerBuilder(Constants::double_type_name, EditorBuilders::ScientificSpinBoxEditorBuilder());
    registerBuilder(Constants::double_type_name, EditorBuilders::ScientificDoubleEditorBuilder());
    registerBuilder(Constants::qcolor_type_name, EditorBuilders::ColorEditorBuilder());
    registerBuilder(Constants::comboproperty_type_name, EditorBuilders::ComboPropertyEditorBuilder());
    registerBuilder(Constants::extproperty_type_name, EditorBuilders::ExternalPropertyEditorBuilder());
}

std::unique_ptr<CustomEditor> DefaultEditorFactory::createEditor(const QModelIndex& index) const
{
    return std::unique_ptr<CustomEditor>(createEditor(itemFromIndex(index)));
}

void DefaultEditorFactory::registerBuilder(const std::string& name, EditorBuilders::builder_t strategy)
{
    // intentional replacement
    m_editor_builders[name] = strategy;
}

CustomEditor* DefaultEditorFactory::createEditor(const SessionItem* item) const
{
    if (!item)
        return nullptr;

    CustomEditor* result(nullptr);

    auto value = item->data(ItemDataRole::DATA);

    if (Utils::IsDoubleVariant(value)) {
//        auto editor = new ScientificDoubleEditor;
//        auto limits = item->data(ItemDataRole::LIMITS);
//        if (limits.isValid())
//            editor->setLimits(limits.value<RealLimits>());
//        result = editor;
        auto editor = new ScientificSpinBoxEditor;
        auto limits = item->data(ItemDataRole::LIMITS);
        if (limits.isValid())
            editor->setLimits(limits.value<RealLimits>());
        editor->setSingleStep(getStep(item->data(ItemDataRole::DATA).toDouble()));
        editor->setDecimals(2);
        result = editor;

    } else if (Utils::IsComboVariant(value))
        result = new ComboPropertyEditor;

    else if (Utils::IsBoolVariant(value))
        result = new BoolEditor;

    else if (Utils::IsColorVariant(value))
        result = new ColorEditor;

    else if (Utils::IsExtPropertyVariant(value))
        result = new ExternalPropertyEditor;

    return result;
}
