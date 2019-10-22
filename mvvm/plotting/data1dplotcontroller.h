// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_DATA1DPLOTCONTROLLER_H
#define MVVM_DATA1DPLOTCONTROLLER_H

#include "itemcontroller.h"

class QCPGraph;

namespace ModelView
{

class Data1DItem;

/*!
@class Data1DPlotController
@brief Establish communication between QCPGraph and Data1DItem.

Provide update of data points on QCPGraph when Graph1DItem is changed.
*/

class CORE_EXPORT Data1DPlotController : public ItemController<Data1DItem>
{
public:
    explicit Data1DPlotController(QCPGraph* graph);
    ~Data1DPlotController() override;

protected:
    void subscribe() override;
    void unsubscribe() override;

private:
    struct Data1DPlotControllerPrivate;
    std::unique_ptr<Data1DPlotControllerPrivate> p_impl;
};

} // namespace ModelView

#endif // MVVM_AXISPLOTCONTROLLERS_H
