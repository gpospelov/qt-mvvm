// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "CustomEditorFactory.h"
#include "ApplicationModels.h"
#include "MaterialModel.h"
#include "MaterialSelectorCellEditor.h"
#include "customvariants.h"
#include <QModelIndex>

using namespace ModelView;

CustomEditorFactory::~CustomEditorFactory() = default;

CustomEditorFactory::CustomEditorFactory(ApplicationModels* models) : m_models(models) {}

std::unique_ptr<CustomEditor>
CustomEditorFactory::createEditor(const QModelIndex& index) const
{
    auto value = index.data(Qt::EditRole);
    if (ModelView::Utils::IsExtPropertyVariant(value))
        return std::make_unique<MaterialSelectorCellEditor>(m_models->materialModel());
    else
        return DefaultEditorFactory::createEditor(index);
}
