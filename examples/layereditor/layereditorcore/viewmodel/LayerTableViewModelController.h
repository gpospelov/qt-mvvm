// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef LAYERTABLEVIEWMODELCONTROLLER_H
#define LAYERTABLEVIEWMODELCONTROLLER_H

#include "abstractviewmodelcontroller.h"

namespace ModelView
{
class AbstractViewModel;
} // namespace ModelView

/*!
@class LayerTableViewModelController
@brief Controller for LayerTableViewModel to show MultiLayerItem in a tree with custom layout.

Will iterate through all top level items and creates rows with layer properties.
*/

class CORE_EXPORT LayerTableViewModelController : public ModelView::AbstractViewModelController
{
public:
    explicit LayerTableViewModelController(ModelView::AbstractViewModel* view_model = nullptr);
};

#endif //  LAYERTABLEVIEWMODELCONTROLLER_H

