// ************************************************************************** //
//                                                                              
//  Model-view-view-model framework for large GUI applications                  
//                                                                              
//! @authors   see AUTHORS                                                      
//! @license   GNU General Public License v3 or higher (see COPYING)            
//                                                                              
// ************************************************************************** //

#ifndef MVVM_PLOTTING_GRAPHCANVAS_H
#define MVVM_PLOTTING_GRAPHCANVAS_H

#include <mvvm/core/export.h>
#include <memory>
#include <QWidget>

namespace ModelView
{

class GraphViewportItem;

/*!
@class GraphCanvas
@brief Widget to show scientific figure with multiple 1D graphs.

Contains embedded QCustomPlot widget, shows content of GraphViewportItem.
*/

class CORE_EXPORT GraphCanvas : public QWidget
{
public:
    explicit GraphCanvas(QWidget* parent = nullptr);
    ~GraphCanvas() override;

    void setItem(GraphViewportItem* viewport_item);

private:
    struct GraphCanvasImpl;
    std::unique_ptr<GraphCanvasImpl> p_impl;
};

} // namespace ModelView

#endif  // MVVM_PLOTTING_GRAPHCANVAS_H
