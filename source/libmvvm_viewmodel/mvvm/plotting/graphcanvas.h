// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_GRAPHCANVAS_H
#define MVVM_PLOTTING_GRAPHCANVAS_H

#include <QWidget>
#include <memory>
#include <mvvm/core/export.h>

namespace ModelView
{

class GraphViewportItem;
class SceneAdapterInterface;

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

    std::unique_ptr<SceneAdapterInterface> createSceneAdapter() const;

private:
    struct GraphCanvasImpl;
    std::unique_ptr<GraphCanvasImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_GRAPHCANVAS_H
