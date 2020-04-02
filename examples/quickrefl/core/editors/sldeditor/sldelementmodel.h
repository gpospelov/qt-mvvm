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

// The mvvm session item associated to a layer
class LayerElementItem;

namespace ModelView
{
class ExternalProperty;
}

//! The model of the sld layer visual representation
class SLDElementModel : public ModelView::SessionModel
{
public:
    SLDElementModel();

    //! Add a layer item
    LayerElementItem* addLayer();
};

#endif //  SLDELEMENTMODEL_H
