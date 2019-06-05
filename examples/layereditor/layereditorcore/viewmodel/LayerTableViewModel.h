// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef LAYERTABLEVIEWMODEL_H
#define LAYERTABLEVIEWMODEL_H

#include "defaultviewmodel.h"
#include "mvvm_global.h"

namespace ModelView
{
class SessionModel;
class SessionItem;
} // namespace ModelView

//! View model to display content of MultiLayerItem in table like views.

class CORE_EXPORT LayerTableViewModel : public ModelView::DefaultViewModel
{
public:
    LayerTableViewModel(ModelView::SessionModel* model = nullptr, QObject* parent = nullptr);
};

#endif //  LAYERTABLEVIEWMODEL_H
