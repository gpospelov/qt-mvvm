// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MATERIALTABLEVIEWMODEL_H
#define MATERIALTABLEVIEWMODEL_H

#include <mvvm/viewmodel/abstractviewmodel.h>

namespace ModelView
{
class SessionModel;
} // namespace ModelView

/*!
@class MaterialTableViewModel
@brief View model to display content of MaterialModel in table like views.
*/

class MaterialTableViewModel : public ModelView::AbstractViewModel
{
public:
    MaterialTableViewModel(ModelView::SessionModel* model = nullptr, QObject* parent = nullptr);
};

#endif //  MATERIALTABLEVIEWMODEL_H
