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
#include "CustomCellDecoration.h"

using namespace ModelView;

CustomModelDelegate::CustomModelDelegate(ApplicationModels* models, QObject* parent)
    : ViewModelDelegate(parent)
{
    setEditorFactory(std::make_unique<CustomEditorFactory>(models));
}
