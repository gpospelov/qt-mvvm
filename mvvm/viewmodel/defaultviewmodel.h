// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_DEFAULTVIEWMODEL_H
#define MVVM_DEFAULTVIEWMODEL_H

#include "abstractviewmodel.h"

namespace ModelView
{

/*!
@class DefaultViewModel
@brief View model to show content of SessionModel in Qt widgets: two column tree with label/data.

Given view model provides two column tree with label/data, with one-to-one child/parent
correspondence as in the original SessionModel.
*/

class CORE_EXPORT DefaultViewModel : public AbstractViewModel
{
public:
    DefaultViewModel(SessionModel* model, QObject* parent = nullptr);
};

} // namespace ModelView

#endif // MVVM_DEFAULTVIEWMODEL_H
