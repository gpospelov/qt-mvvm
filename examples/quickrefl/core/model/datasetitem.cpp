// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "datasetitem.h"
#include "item_constants.h"
#include <mvvm/standarditems/containeritem.h>

DataSetItem::DataSetItem() : ModelView::CompoundItem(::Constants::DataSetItemType)
{
    addProperty<ModelView::ContainerItem>(P_DATA);
    addProperty<ModelView::ContainerItem>(P_VIEWPORTS);
}

//! Retuns container with Data1DItem's.

ModelView::ContainerItem* DataSetItem::dataContainer() const
{
    return item<ModelView::ContainerItem>(P_DATA);
}

ModelView::ContainerItem* DataSetItem::viewportContainer() const
{
    return item<ModelView::ContainerItem>(P_VIEWPORTS);
}
