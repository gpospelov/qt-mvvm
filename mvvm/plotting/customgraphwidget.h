// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_CUSTOMGRAPHWIDGET_H
#define MVVM_CUSTOMGRAPHWIDGET_H

#include "mvvm_export.h"
#include <memory>
#include <QWidget>

namespace ModelView
{

/*!
@class CustomGraphWidget
@brief Widget to show scientific figure with multiple 1D graphs.

Contains embedded QCustomPlot widget, shows content of GraphViewportItem.
*/

class CORE_EXPORT CustomGraphWidget : public QWidget
{
public:
    explicit CustomGraphWidget(QWidget* parent = nullptr);

private:
    struct CustomGraphWidgetPrivate;
    std::unique_ptr<CustomGraphWidgetPrivate> p_impl;
};

} // namespace ModelView

#endif // MVVM_CUSTOMGRAPHWIDGET_H
