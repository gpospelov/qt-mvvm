// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "CustomEditorFactory.h"
#include "ApplicationModels.h"
#include "MaterialModel.h"
#include "MaterialSelectorCellEditor.h"
#include <mvvm/model/customvariants.h>
#include <QModelIndex>

using namespace ModelView;

CustomEditorFactory::~CustomEditorFactory() = default;

CustomEditorFactory::CustomEditorFactory(ApplicationModels* models) : m_models(models) {}

std::unique_ptr<CustomEditor>
CustomEditorFactory::createEditor(const QModelIndex& index) const
{
    auto value = index.data(Qt::EditRole);
    if (Utils::IsExtPropertyVariant(value))
        return std::make_unique<MaterialSelectorCellEditor>(m_models->materialModel());
    else
        return DefaultEditorFactory::createEditor(index);
}
