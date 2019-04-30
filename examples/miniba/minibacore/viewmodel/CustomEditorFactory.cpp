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

CustomEditorFactory::~CustomEditorFactory() = default;

std::unique_ptr<ModelView::CustomEditor>
CustomEditorFactory::createEditor(const QModelIndex& index) const
{
    return DefaultEditorFactory::createEditor(index);
}
