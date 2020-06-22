// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_CHILDRENSTRATEGYINTERFACE_H
#define MVVM_VIEWMODEL_CHILDRENSTRATEGYINTERFACE_H

#include <QList>
#include <mvvm_viewmodel_export.h>

class QStandardItem;

namespace ModelView
{

class SessionItem;

//! Base class for strategies to find children, actual of fictional, of given item.
//!
//! Reported vector of children might be different from actual children of given item.
//! The strategy is used in context of AbstractViewModel while exposing SessionModel to Qt.
//! Thanks to this strategy ViewModel decides which items to visit.

class MVVM_VIEWMODEL_EXPORT ChildrenStrategyInterface
{
public:
    virtual ~ChildrenStrategyInterface() = default;

    //! Returns vector of children of given item.
    virtual std::vector<SessionItem*> children(const SessionItem* item) const = 0;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_CHILDRENSTRATEGYINTERFACE_H
