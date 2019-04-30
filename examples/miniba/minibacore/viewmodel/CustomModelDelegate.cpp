// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "CustomModelDelegate.h"
#include "CustomEditorFactory.h"


CustomModelDelegate::CustomModelDelegate(ApplicationModels* models, QObject* parent)
    : ModelView::ViewModelDelegate(parent)
{
    setEditorFactory(std::make_unique<CustomEditorFactory>(models));
}
