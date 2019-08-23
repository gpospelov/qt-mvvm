// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_AXESPLOTCONTROLLER_H
#define MVVM_AXESPLOTCONTROLLER_H


#include "itemcontroller.h"

class QCustomPlot;
class QCPAxis;

namespace ModelView
{

class ViewportAxisItem;

/*!
@class AxesPlotController
@brief Establish communication between QCPAxis and ViewportAxisItem.

Provide mutual update of axis parameters (min, max, title) for two axes representations.
*/

class CORE_EXPORT AxesPlotController : public ItemController
{
public:
    explicit AxesPlotController(QCustomPlot* plot, QObject* parent = nullptr);
    ~AxesPlotController() override;

    void subscribe() override;

protected:
    ViewportAxisItem* axisItem();
    QCPAxis* customAxis();

private:
    struct AxesPlotControllerPrivate;
    std::unique_ptr<AxesPlotControllerPrivate> p_impl;
};


} // namespace ModelView

#endif // MVVM_AXESPLOTCONTROLLER_H
