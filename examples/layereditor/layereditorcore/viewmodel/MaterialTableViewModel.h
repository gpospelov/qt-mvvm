// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MATERIALTABLEVIEWMODEL_H
#define MATERIALTABLEVIEWMODEL_H

#include "defaultviewmodel.h"
#include "mvvm_global.h"

namespace ModelView
{
class SessionModel;
class SessionItem;
} // namespace ModelView

//! View model to display content of MaterialModel in table like views.

class CORE_EXPORT MaterialTableViewModel : public ModelView::DefaultViewModel
{
public:
    MaterialTableViewModel(ModelView::SessionModel* model = nullptr, QObject* parent = nullptr);
};

#endif //  MATERIALTABLEVIEWMODEL_H
