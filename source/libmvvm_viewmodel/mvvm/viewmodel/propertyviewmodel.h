// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_PROPERTYVIEWMODEL_H
#define MVVM_VIEWMODEL_PROPERTYVIEWMODEL_H

#include <mvvm/viewmodel/viewmodel.h>

namespace ModelView
{

//! View model to show content of SessionModel in Qt widgets.
//! Only property items are shown, also hides inactive items of GroupProperty.

class CORE_EXPORT PropertyViewModel : public ViewModel
{
public:
    PropertyViewModel(SessionModel* model, QObject* parent = nullptr);
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_PROPERTYVIEWMODEL_H
