// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_GRAPHITEMCONTROLLER_H
#define MVVM_GRAPHITEMCONTROLLER_H

#include "itemcontroller.h"

class QCustomPlot;

namespace ModelView
{

class GraphItem;

/*!
@class GraphItemController
@brief Establish communication between QCPGraph and GraphItem.

Provide update on QCPGraph (data points, line style, color, etc) when GraphItem is changed.
*/

class CORE_EXPORT GraphItemController : public ItemController<GraphItem>
{
public:
    explicit GraphItemController(QCustomPlot* plot);
    ~GraphItemController() override;

protected:
    void subscribe() override;

private:
    struct GraphItemControllerPrivate;
    std::unique_ptr<GraphItemControllerPrivate> p_impl;
};

} // namespace ModelView

#endif // MVVM_AXISPLOTCONTROLLERS_H
