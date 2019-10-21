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

#include "viewportitem.h"

namespace ModelView
{

class GraphItem;
class ViewportAxisItem;

/*!
@class GraphViewportItem
@brief Container with viewport and collection of GraphItem's to plot.
*/

class CORE_EXPORT GraphViewportItem : public ViewportItem
{
public:
    GraphViewportItem();

    std::vector<GraphItem*> graphItems() const;

private:
    std::pair<double, double> data_xrange() const override;
    std::pair<double, double> data_yrange() const override;
};

} // namespace ModelView

#endif // MVVM_GRAPHVIEWPORTITEM_H
