// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_AXESITEMS_H
#define MVVM_AXESITEMS_H

#include "compounditem.h"

namespace ModelView
{

//! Items for axes.

class CORE_EXPORT BasicAxisItem : public CompoundItem
{
public:
    explicit BasicAxisItem(std::string model_type);
};

//! Item to represent fixed bin axis.

class CORE_EXPORT FixedBinAxisItem : public BasicAxisItem
{
public:
    static inline const std::string P_NBINS = "P_NBINS";
    static inline const std::string P_XMIN = "P_XMIN";
    static inline const std::string P_XMAX = "P_XMAX";

    FixedBinAxisItem();
};

} // namespace ModelView

#endif // MVVM_AXESITEMS_H
