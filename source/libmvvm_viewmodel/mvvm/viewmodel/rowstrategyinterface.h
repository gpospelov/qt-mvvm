// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_ROWSTRATEGYINTERFACE_H
#define MVVM_VIEWMODEL_ROWSTRATEGYINTERFACE_H

#include <QList>
#include <mvvm/core/export.h>
#include <vector>
#include <memory>
#include <stdexcept>

class QStandardItem;

namespace ModelView
{

class SessionItem;
class RefViewItem;

/*!
@class RowStrategyInterface
@brief Base class to construct row of QStandardItems from given SessionItem.

Used in context of AbstractViewModel while exposing SessionModel to Qt.
*/

class CORE_EXPORT RowStrategyInterface
{
public:
    virtual ~RowStrategyInterface() = default;

    virtual QStringList horizontalHeaderLabels() const = 0;

    virtual std::vector<std::unique_ptr<RefViewItem>> constructRefRow(SessionItem*) = 0;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_ROWSTRATEGYINTERFACE_H
