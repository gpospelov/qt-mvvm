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

Provide data points update on QCPGraph when GraphItem is changed.
*/

class CORE_EXPORT GraphItemController : public ItemControllerV2<GraphItem>
{
public:
    explicit GraphItemController(QCustomPlot* plot);
    ~GraphItemController() override;

protected:
    void subscribe() override;
    QCustomPlot* customPlot();

private:
    struct GraphItemControllerPrivate;
    std::unique_ptr<GraphItemControllerPrivate> p_impl;
};

} // namespace ModelView

#endif // MVVM_AXISPLOTCONTROLLERS_H
