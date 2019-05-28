// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_ROWCONSTRUCTORINTERFACE_H
#define MVVM_ROWCONSTRUCTORINTERFACE_H

#include "mvvm_global.h"
#include <QList>

class QStandardItem;

namespace ModelView {

class SessionItem;

//! Base class to construct row of QStandardItems from given SessionItem.
//! Used in context of AbstractViewModel while exposing SessionModel to Qt.

class CORE_EXPORT RowConstructorInterface
{
public:
    virtual ~RowConstructorInterface() = default;

    //! Construct row of QStandardItems from given SessionItem.
    virtual QList<QStandardItem*> constructRow(SessionItem* item) = 0;

    //! Returns number of elements in a row.
    virtual int columnCount() const = 0;

    virtual QStringList horizontalHeaderLabels() const = 0;
};

}  // namespace ModelView

#endif // MVVM_ROWCONSTRUCTORINTERFACE_H
