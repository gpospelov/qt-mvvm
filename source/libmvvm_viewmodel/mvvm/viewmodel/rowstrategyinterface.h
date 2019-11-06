// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_ROWSTRATEGYINTERFACE_H
#define MVVM_VIEWMODEL_ROWSTRATEGYINTERFACE_H

#include <mvvm/core/export.h>
#include <QList>

class QStandardItem;

namespace ModelView {

class SessionItem;

/*!
@class RowStrategyInterface
@brief Base class to construct row of QStandardItems from given SessionItem.

Used in context of AbstractViewModel while exposing SessionModel to Qt.
*/

class CORE_EXPORT RowStrategyInterface
{
public:
    virtual ~RowStrategyInterface() = default;

    //! Construct row of QStandardItems from given SessionItem.
    virtual QList<QStandardItem*> constructRow(SessionItem* item) = 0;

    virtual QStringList horizontalHeaderLabels() const = 0;
};

}  // namespace ModelView

#endif  // MVVM_VIEWMODEL_ROWSTRATEGYINTERFACE_H
