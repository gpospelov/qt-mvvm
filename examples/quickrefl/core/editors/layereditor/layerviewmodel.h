// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef LAYERVIEWMODEL_H
#define LAYERVIEWMODEL_H

#include <mvvm/viewmodel/abstractviewmodel.h>

namespace ModelView
{
class SessionModel;
} // namespace ModelView

/*!
@class LayerViewModel
@brief View model to display content of MultiLayerItem in table like views.
*/

class LayerViewModel : public ModelView::AbstractViewModel
{
public:
    LayerViewModel(ModelView::SessionModel* model, QObject* parent = nullptr);
};

#endif //  LAYERVIEWMODEL_H
