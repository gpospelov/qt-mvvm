// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef LAYERVIEWMODELCONTROLLER_H
#define LAYERVIEWMODELCONTROLLER_H

#include <mvvm/viewmodel/abstractviewmodelcontroller.h>

namespace ModelView
{
class ViewModel;
} // namespace ModelView

/*!
@class LayerViewModelController
@brief Controller for LayerViewModel to show MultiLayerItem in a tree with custom layout.

Will iterate through all top level items and creates rows with layer properties.
*/

class LayerViewModelController : public ModelView::AbstractViewModelController
{
public:
    explicit LayerViewModelController(ModelView::SessionModel* model,
                                      ModelView::ViewModel* view_model);
};

#endif //  LAYERVIEWMODELCONTROLLER_H
