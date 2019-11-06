// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_DATA1DPLOTCONTROLLER_H
#define MVVM_PLOTTING_DATA1DPLOTCONTROLLER_H

#include <mvvm/signals/itemcontroller.h>
#include <memory>

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
    struct Data1DPlotControllerImpl;
    std::unique_ptr<Data1DPlotControllerImpl> p_impl;
};

} // namespace ModelView

#endif  // MVVM_PLOTTING_DATA1DPLOTCONTROLLER_H
