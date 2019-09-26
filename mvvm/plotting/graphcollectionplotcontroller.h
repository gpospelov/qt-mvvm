// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_GRAPHCOLLECTIONPLOTCONTROLLER_H
#define MVVM_GRAPHCOLLECTIONPLOTCONTROLLER_H

#include "itemcontroller.h"

class QCustomPlot;

namespace ModelView
{

class GraphViewportItem;

/*!
@class GraphCollectionPlotController
@brief Populates custom plot with all graphs found in GraphViewportItem.
*/

class CORE_EXPORT GraphCollectionPlotController : public ItemController<GraphViewportItem>
{
public:
    explicit GraphCollectionPlotController(QCustomPlot* plot);
    ~GraphCollectionPlotController() override;

protected:
    void subscribe() override;

private:
    struct GraphCollectionPlotControllerPrivate;
    std::unique_ptr<GraphCollectionPlotControllerPrivate> p_impl;
};

} // namespace ModelView

#endif // MVVM_GRAPHCOLLECTIONPLOTCONTROLLER_H
