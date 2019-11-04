// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_PROPERTYVIEWMODEL_H
#define MVVM_PROPERTYVIEWMODEL_H

#include "abstractviewmodel.h"

namespace ModelView
{

//! View model to show content of SessionModel in Qt widgets.
//! Only property items are shown, also hides inactive items of GroupProperty.

class CORE_EXPORT PropertyViewModel : public AbstractViewModel
{
public:
    PropertyViewModel(SessionModel* model = nullptr, QObject* parent = nullptr);
};

} // namespace ModelView

#endif // MVVM_PROPERTYVIEWMODEL_H
