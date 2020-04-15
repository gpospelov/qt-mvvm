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
#include <mvvm/model/variant-constants.h>
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
    registerBuilder(Constants::bool_type_name, EditorBuilders::BoolEditorBuilder());
    registerBuilder(Constants::int_type_name, EditorBuilders::IntegerEditorBuilder());
    //    registerBuilder(Constants::double_type_name, EditorBuilders::DoubleEditorBuilder());
    registerBuilder(Constants::double_type_name, EditorBuilders::ScientificSpinBoxEditorBuilder());
    //    registerBuilder(Constants::double_type_name,
    //    EditorBuilders::ScientificDoubleEditorBuilder());
    registerBuilder(Constants::qcolor_type_name, EditorBuilders::ColorEditorBuilder());
    registerBuilder(Constants::comboproperty_type_name,
                    EditorBuilders::ComboPropertyEditorBuilder());
    registerBuilder(Constants::extproperty_type_name,
                    EditorBuilders::ExternalPropertyEditorBuilder());
}

std::unique_ptr<CustomEditor> DefaultEditorFactory::createEditor(const QModelIndex& index) const
{
    auto item = itemFromIndex(index);
    if (!item)
        return {};

    auto value = item->data<QVariant>();
    auto builder = findBuilder(Utils::VariantName(value));
    return builder ? builder(item) : std::unique_ptr<CustomEditor>();
}

void DefaultEditorFactory::registerBuilder(const std::string& name,
                                           EditorBuilders::builder_t strategy)
{
    // intentional replacement
    m_editor_builders[name] = std::move(strategy);
}

//! Returns builder for variant with given name.

EditorBuilders::builder_t DefaultEditorFactory::findBuilder(const std::string& name) const
{
    auto it = m_editor_builders.find(name);
    return it != m_editor_builders.end() ? it->second : EditorBuilders::builder_t();
}
