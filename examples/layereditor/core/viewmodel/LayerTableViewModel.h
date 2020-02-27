// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef LAYERTABLEVIEWMODEL_H
#define LAYERTABLEVIEWMODEL_H

#include <mvvm/viewmodel/viewmodel.h>

namespace ModelView
{
class SessionModel;
} // namespace ModelView

/*!
@class LayerTableViewModel
@brief View model to display content of MultiLayerItem in table like views.
*/

class LayerTableViewModel : public ModelView::ViewModel
{
public:
    LayerTableViewModel(ModelView::SessionModel* model, QObject* parent = nullptr);
};

#endif //  LAYERTABLEVIEWMODEL_H
