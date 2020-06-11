// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <viewmodel/custommodeldelegate.h>
#include <viewmodel/customeditorfactory.h>

using namespace ModelView;

CustomModelDelegate::CustomModelDelegate(ApplicationModels* models, QObject* parent)
    : ViewModelDelegate(parent)
{
    setEditorFactory(std::make_unique<CustomEditorFactory>(models));
}
