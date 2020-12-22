// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_DATA1DPLOTCONTROLLER_H
#define MVVM_PLOTTING_DATA1DPLOTCONTROLLER_H

#include "mvvm/signals/itemlistener.h"
#include "mvvm/view_export.h"
#include <memory>

class QCPGraph;

namespace ModelView {

class Data1DItem;

//! Establishes communication between QCPGraph and Data1DItem.
//! Provides update of data points on QCPGraph when Graph1DItem is changed.

class MVVM_VIEW_EXPORT Data1DPlotController : public ItemListener<Data1DItem> {
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

#endif // MVVM_PLOTTING_DATA1DPLOTCONTROLLER_H
