// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/editors/customeditor.h>
#include <mvvm/editors/defaulteditorfactory.h>
#include <mvvm/editors/editor_constants.h>
#include <mvvm/model/customvariants.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/variant_constants.h>
#include <mvvm/viewmodel/viewmodel.h>

using namespace ModelView;

namespace
{

const SessionItem* itemFromIndex(const QModelIndex& index)
{
    auto model = dynamic_cast<const ViewModel*>(index.model());
    return model ? model->sessionItemFromIndex(index) : nullptr;
}

} // namespace

DefaultEditorFactory::~DefaultEditorFactory() = default;

DefaultEditorFactory::DefaultEditorFactory()
{
    initBuildersForVariantName();
    initBuildersForEditorType();
}

//! Creates editor for given model index. It is expected that the index belongs to a ViewModel.

std::unique_ptr<CustomEditor> DefaultEditorFactory::createEditor(const QModelIndex& index) const
{
    auto item = itemFromIndex(index);
    if (!item)
        return {};

    auto value = item->data<QVariant>();
    auto builder = findBuilderForVariant(Utils::VariantName(value));
    return builder ? builder(item) : std::unique_ptr<CustomEditor>();
}

//! Creates map of builders to retrieve the builder from variant name.

void DefaultEditorFactory::initBuildersForVariantName()
{
    registerBuilderForVariant(Constants::bool_type_name, EditorBuilders::BoolEditorBuilder());
    registerBuilderForVariant(Constants::int_type_name, EditorBuilders::IntegerEditorBuilder());
    registerBuilderForVariant(Constants::double_type_name,
                              EditorBuilders::ScientificSpinBoxEditorBuilder());
    registerBuilderForVariant(Constants::qcolor_type_name, EditorBuilders::ColorEditorBuilder());
    registerBuilderForVariant(Constants::comboproperty_type_name,
                              EditorBuilders::ComboPropertyEditorBuilder());
    registerBuilderForVariant(Constants::extproperty_type_name,
                              EditorBuilders::ExternalPropertyEditorBuilder());
}

//! Creates map of builders to retrieve the builder from editor type.

void DefaultEditorFactory::initBuildersForEditorType()
{
    registerBuilderForEditor(Constants::BoolEditorType, EditorBuilders::BoolEditorBuilder());
    registerBuilderForEditor(Constants::ColorEditorType, EditorBuilders::ColorEditorBuilder());
    registerBuilderForEditor(Constants::ComboPropertyEditorType,
                             EditorBuilders::ComboPropertyEditorBuilder());
    registerBuilderForEditor(Constants::DoubleEditorType, EditorBuilders::DoubleEditorBuilder());
    registerBuilderForEditor(Constants::ExternalPropertyEditorType,
                             EditorBuilders::ExternalPropertyEditorBuilder());
    registerBuilderForEditor(Constants::IntegerEditorType, EditorBuilders::IntegerEditorBuilder());
    registerBuilderForEditor(Constants::ScientficDoubleEditorType,
                             EditorBuilders::ScientificDoubleEditorBuilder());
    registerBuilderForEditor(Constants::ScientficSpinBoxEditorType,
                             EditorBuilders::ScientificSpinBoxEditorBuilder());
    registerBuilderForEditor(Constants::SelectableComboPropertyEditorType,
                             EditorBuilders::SelectableComboPropertyEditorBuilder());
}

void DefaultEditorFactory::registerBuilderForVariant(const std::string& variant_type,
                                                     EditorBuilders::builder_t builder)
{
    m_variantNameToBuilderMap[variant_type] = std::move(builder);
}

void DefaultEditorFactory::registerBuilderForEditor(const std::string& editor_type,
                                                    EditorBuilders::builder_t builder)
{
    m_variantNameToBuilderMap[editor_type] = std::move(builder);
}

//! Returns builder for variant with given name.

EditorBuilders::builder_t
DefaultEditorFactory::findBuilderForVariant(const std::string& variant_name) const
{
    auto it = m_variantNameToBuilderMap.find(variant_name);
    return it != m_variantNameToBuilderMap.end() ? it->second : EditorBuilders::builder_t();
}

//! Returns builder for editor with given name.

EditorBuilders::builder_t DefaultEditorFactory::findBuilderForEditor(const std::string &editor_type) const
{
    auto it = m_editorTypeToBuilderMap.find(editor_type);
    return it != m_editorTypeToBuilderMap.end() ? it->second : EditorBuilders::builder_t();
}
