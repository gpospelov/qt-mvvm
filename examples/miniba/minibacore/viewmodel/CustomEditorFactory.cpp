// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "CustomEditorFactory.h"
#include "customeditor.h"
#include "MaterialSelectorCellEditor.h"
#include "customvariants.h"
#include <QModelIndex>

CustomEditorFactory::~CustomEditorFactory() = default;

std::unique_ptr<ModelView::CustomEditor>
CustomEditorFactory::createEditor(const QModelIndex& index) const
{
    auto value = index.data(Qt::EditRole);
    if (ModelView::Utils::IsExtPropertyVariant(value))
        return std::make_unique<MaterialSelectorCellEditor>();
    else
        return DefaultEditorFactory::createEditor(index);
}
