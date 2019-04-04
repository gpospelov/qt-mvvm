// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "editorfactory.h"
#include <QModelIndex>

using namespace ModelView;

EditorFactory::EditorFactory()
{

}

QWidget* ModelView::EditorFactory::createEditor(const QModelIndex& index) const
{
    Q_UNUSED(index)
    return nullptr;
}
