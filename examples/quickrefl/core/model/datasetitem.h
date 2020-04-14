// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef DATASETITEM_H
#define DATASETITEM_H

#include <mvvm/model/compounditem.h>

namespace ModelView
{
class ContainerItem;
} // namespace ModelView

//! Holds collection of data items and collection of viewports representing
//! imported experimental data.

class DataSetItem : public ModelView::CompoundItem
{
public:
    static inline const std::string P_DATA = "P_DATA";
    static inline const std::string P_VIEWPORTS = "P_VIEWPORTS";

    DataSetItem();

    ModelView::ContainerItem* dataContainer() const;

    ModelView::ContainerItem* viewportContainer() const;
};

#endif // DATASETITEM_H
