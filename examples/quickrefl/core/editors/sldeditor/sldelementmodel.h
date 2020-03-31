// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SLDELEMENTMODEL_H
#define SLDELEMENTMODEL_H

#include <mvvm/model/sessionmodel.h>
#include <vector>

class LayerElementItem;

namespace ModelView
{
class ExternalProperty;
}

/*!
@class ViewItemsModel
@brief This holds the model for all the graphical elements of the sld editor
*/

class SLDElementModel : public ModelView::SessionModel
{
public:
    SLDElementModel();

    //! Add a layer item
    LayerElementItem* addLayer();
};

#endif //  SLDELEMENTMODEL_H
