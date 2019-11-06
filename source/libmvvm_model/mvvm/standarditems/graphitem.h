// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_STANDARDITEMS_GRAPHITEM_H
#define MVVM_STANDARDITEMS_GRAPHITEM_H

#include <mvvm/model/compounditem.h>

namespace ModelView
{

class Data1DItem;

/*!
@class GraphItem
@brief One-dimensional graph representation of Data1DItem.

Contains plot properties (i.e. color, line type etc) and link to Data1DItem, which will provide
actual data to plot. GraphItem is intended for plotting only via GraphViewportItem.
*/

class CORE_EXPORT GraphItem : public CompoundItem
{
public:
    static inline const std::string P_LINK = "P_LINK";
    static inline const std::string P_COLOR = "P_COLOR";
    static inline const std::string P_GRAPH_TITLE = "P_GRAPH_TITLE";
    GraphItem();

    void setDataItem(const Data1DItem* item);

    Data1DItem* dataItem() const;

    std::vector<double> binCenters() const;

    std::vector<double> binValues() const;
};

} // namespace ModelView

#endif  // MVVM_STANDARDITEMS_GRAPHITEM_H
