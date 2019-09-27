// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_GRAPHVIEWPORTITEM_H
#define MVVM_GRAPHVIEWPORTITEM_H

#include "compounditem.h"

namespace ModelView
{

/*!
@class GraphViewportItem
@brief Container with viewport and collection of GraphItem's to plot.
*/

class CORE_EXPORT GraphViewportItem : public CompoundItem
{
public:
    static inline const std::string P_XAXIS = "P_XAXIS";
    static inline const std::string P_YAXIS = "P_YAXIS";
    static inline const std::string T_GRAPHS = "T_GRAPHS";
    GraphViewportItem();

    void update_viewport();

    void update_xaxis_range();

    void update_yaxis_range();
};

} // namespace ModelView

#endif // MVVM_GRAPHVIEWPORTITEM_H
