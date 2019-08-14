// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_DATA1DITEM_H
#define MVVM_DATA1DITEM_H

#include "compounditem.h"
#include <vector>

namespace ModelView
{

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

    void setFixedBinAxis(int nbins, double xmin, double xmax);

    void setContent(const std::vector<double>& data);

    std::vector<double> binCenters() const;

    std::vector<double> binValues() const;
};

} // namespace ModelView

#endif // MVVM_DATA1DITEM_H
