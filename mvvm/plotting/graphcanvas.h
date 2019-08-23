// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_GRAPHCANVAS_H
#define MVVM_GRAPHCANVAS_H

#include "mvvm_export.h"
#include <memory>
#include <QWidget>

class QCustomPlot;

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

    void setItem(GraphViewportItem* item);

private:
    struct GraphCanvasPrivate;
    std::unique_ptr<GraphCanvasPrivate> p_impl;
};

} // namespace ModelView

#endif // MVVM_GRAPHCANVAS_H
