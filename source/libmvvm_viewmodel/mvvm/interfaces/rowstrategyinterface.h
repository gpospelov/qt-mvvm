// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_INTERFACES_ROWSTRATEGYINTERFACE_H
#define MVVM_INTERFACES_ROWSTRATEGYINTERFACE_H

#include "mvvm/viewmodel_export.h"
#include <QStringList>
#include <memory>
#include <vector>

namespace ModelView {

class SessionItem;
class ViewItem;

//! Base class to construct row of ViewItem's from given SessionItem.
//! Used in context of AbstractViewModel while exposing SessionModel to Qt.

class MVVM_VIEWMODEL_EXPORT RowStrategyInterface {
public:
    virtual ~RowStrategyInterface() = default;

    virtual QStringList horizontalHeaderLabels() const = 0;

    virtual std::vector<std::unique_ptr<ViewItem>> constructRow(SessionItem*) = 0;
};

} // namespace ModelView

#endif // MVVM_INTERFACES_ROWSTRATEGYINTERFACE_H
