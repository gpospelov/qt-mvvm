// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_INTERFACES_CHILDRENSTRATEGYINTERFACE_H
#define MVVM_INTERFACES_CHILDRENSTRATEGYINTERFACE_H

#include "mvvm/viewmodel_export.h"
#include <vector>

namespace ModelView {

class SessionItem;

//! Base class for strategies to find children, actual or fictional, of a given item.
//! The reported vector of children might be different from the actual children of a given item.
//! The strategy is used in the context of AbstractViewModel while exposing SessionModel to Qt.
//! Thanks to this strategy ViewModel decides which items to visit.

class MVVM_VIEWMODEL_EXPORT ChildrenStrategyInterface {
public:
    virtual ~ChildrenStrategyInterface() = default;

    //! Returns vector of children of given item.
    virtual std::vector<SessionItem*> children(const SessionItem* item) const = 0;
};

} // namespace ModelView

#endif // MVVM_INTERFACES_CHILDRENSTRATEGYINTERFACE_H
