// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_PLOTTING_AXISTITLECONTROLLER_H
#define MVVM_PLOTTING_AXISTITLECONTROLLER_H

#include "mvvm/signals/itemlistener.h"
#include "mvvm/view_export.h"
#include <memory>

class QCPAxis;

namespace ModelView {

class TextItem;

//! Propagates title settings from TextItem to QCPAxis.

class MVVM_VIEW_EXPORT AxisTitleController : public ItemListener<TextItem> {
public:
    explicit AxisTitleController(QCPAxis* axis);
    ~AxisTitleController() override;

protected:
    void subscribe() override;

public:
    struct AxisTitleControllerImpl;
    std::unique_ptr<AxisTitleControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_PLOTTING_AXISTITLECONTROLLER_H
