// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_COLORMAPCANVAS_H
#define MVVM_COLORMAPCANVAS_H

#include "mvvm_export.h"
#include <memory>
#include <QWidget>

class QCustomPlot;

namespace ModelView
{

class ColorMapViewportItem;

/*!
@class ColorMapCanvas
@brief Widget to show 2D data as color map.

Contains embedded QCustomPlot widget, shows content of ColorMapViewportItem.
*/

class CORE_EXPORT ColorMapCanvas : public QWidget
{
public:
    explicit ColorMapCanvas(QWidget* parent = nullptr);
    ~ColorMapCanvas() override;

    void setItem(ColorMapViewportItem* viewport_item);

private:
    struct ColorMapCanvasImpl;
    std::unique_ptr<ColorMapCanvasImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_COLORMAPCANVAS_H
