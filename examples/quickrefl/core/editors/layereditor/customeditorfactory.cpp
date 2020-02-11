// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "customeditorfactory.h"
#include "applicationmodels.h"
#include "materialmodel.h"
#include <QModelIndex>
#include <algorithm>
#include <mvvm/editors/externalpropertycomboeditor.h>
#include <mvvm/model/customvariants.h>
#include <mvvm/model/externalproperty.h>

namespace
{
//! Return list of possible choices for material properties in MaterialModel.
//! Use "undefined material" as a first item in a list.
std::vector<ModelView::ExternalProperty> get_choice_of_materials(MaterialModel* model)
{
    std::vector<ModelView::ExternalProperty> result{model->undefined_material()};
    auto other_data = model->material_data();
    std::copy(other_data.begin(), other_data.end(), std::back_inserter(result));
    return result;
}
} // namespace

using namespace ModelView;

CustomEditorFactory::~CustomEditorFactory() = default;

CustomEditorFactory::CustomEditorFactory(ApplicationModels* models) : m_models(models) {}

std::unique_ptr<CustomEditor> CustomEditorFactory::createEditor(const QModelIndex& index) const
{
    auto value = index.data(Qt::EditRole);
    if (Utils::IsExtPropertyVariant(value)) {
        auto material_choice_callback = [this]() {
            return get_choice_of_materials(m_models->materialModel());
        };
        return std::make_unique<ExternalPropertyComboEditor>(material_choice_callback);
    } else {
        return DefaultEditorFactory::createEditor(index);
    }
}
