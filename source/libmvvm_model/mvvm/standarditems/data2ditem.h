// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_STANDARDITEMS_DATA2DITEM_H
#define MVVM_STANDARDITEMS_DATA2DITEM_H

#include "mvvm/model/compounditem.h"
#include <vector>

namespace ModelView {

class BinnedAxisItem;

//! Represents two-dimensional data (axes definition and 2d array of values).
//! Values are stored in Data2DItem itself, axes are attached as children. Corresponding plot
//! properties will be served by ColorMapItem.

class MVVM_MODEL_EXPORT Data2DItem : public CompoundItem {
public:
    static inline const std::string P_VALUES = "P_VALUES";
    static inline const std::string T_XAXIS = "T_XAXIS";
    static inline const std::string T_YAXIS = "T_YAXIS";

    Data2DItem();

    void setAxes(std::unique_ptr<BinnedAxisItem> x_axis, std::unique_ptr<BinnedAxisItem> y_axis);

    BinnedAxisItem* xAxis() const;

    BinnedAxisItem* yAxis() const;

    void setContent(const std::vector<double>& data);

    std::vector<double> content() const;

private:
    void insert_axis(std::unique_ptr<BinnedAxisItem> axis, const std::string& tag);
};

} // namespace ModelView

#endif // MVVM_STANDARDITEMS_DATA2DITEM_H
