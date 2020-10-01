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
    registerBuilderForVariant(Constants::bool_type_name, EditorBuilders::BoolEditorBuilder());
    registerBuilderForVariant(Constants::int_type_name, EditorBuilders::IntegerEditorBuilder());
    //    registerBuilder(Constants::double_type_name, EditorBuilders::DoubleEditorBuilder());
    registerBuilderForVariant(Constants::double_type_name,
                              EditorBuilders::ScientificSpinBoxEditorBuilder());
    //    registerBuilder(Constants::double_type_name,
    //    EditorBuilders::ScientificDoubleEditorBuilder());
    registerBuilderForVariant(Constants::qcolor_type_name, EditorBuilders::ColorEditorBuilder());
    registerBuilderForVariant(Constants::comboproperty_type_name,
                              EditorBuilders::ComboPropertyEditorBuilder());
    registerBuilderForVariant(Constants::extproperty_type_name,
                              EditorBuilders::ExternalPropertyEditorBuilder());
}

std::unique_ptr<CustomEditor> DefaultEditorFactory::createEditor(const QModelIndex& index) const
{
    auto item = itemFromIndex(index);
    if (!item)
        return {};

    auto value = item->data<QVariant>();
    auto builder = findBuilderForVariant(Utils::VariantName(value));
    return builder ? builder(item) : std::unique_ptr<CustomEditor>();
}

void DefaultEditorFactory::registerBuilderForVariant(const std::string& variant_type,
                                                     EditorBuilders::builder_t builder)
{
    // intentional replacement
    m_variantNameToBuilderMap[variant_type] = std::move(builder);
}

//! Returns builder for variant with given name.

EditorBuilders::builder_t
DefaultEditorFactory::findBuilderForVariant(const std::string& variant_name) const
{
    auto it = m_variantNameToBuilderMap.find(variant_name);
    return it != m_variantNameToBuilderMap.end() ? it->second : EditorBuilders::builder_t();
}
