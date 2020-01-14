// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_STANDARDITEMS_DATA1DITEM_H
#define MVVM_STANDARDITEMS_DATA1DITEM_H

#include <mvvm/model/compounditem.h>
#include <vector>

namespace ModelView
{

class BinnedAxisItem;

/*!
@class Data1DItem
@brief Represents bare one-dimensional data (axis and values).

Values are stored in Data1DItem itself, axis is attached as a child. Corresponding plot
properties will be served by GraphItem.
*/

class CORE_EXPORT Data1DItem : public CompoundItem
{
public:
    static inline const std::string T_AXIS = "T_AXIS";
    Data1DItem();

    void setAxis(std::unique_ptr<BinnedAxisItem> axis);

    void setContent(const std::vector<double>& data);

    std::vector<double> binCenters() const;

    std::vector<double> binValues() const;
};

} // namespace ModelView

#endif // MVVM_STANDARDITEMS_DATA1DITEM_H
