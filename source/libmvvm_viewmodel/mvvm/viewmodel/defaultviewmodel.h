// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_DEFAULTVIEWMODEL_H
#define MVVM_VIEWMODEL_DEFAULTVIEWMODEL_H

#include <mvvm/viewmodel/viewmodel.h>

namespace ModelView
{

/*!
@class DefaultViewModel
@brief View model to show content of SessionModel in Qt widgets: two column tree with label/data.

Given view model provides two column tree with label/data, with one-to-one child/parent
correspondence as in the original SessionModel.
*/

class CORE_EXPORT DefaultViewModel : public ViewModel
{
public:
    DefaultViewModel(SessionModel* model, QObject* parent = nullptr);
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_DEFAULTVIEWMODEL_H
