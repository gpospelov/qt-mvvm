// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODELINTERFACES_H
#define MVVM_VIEWMODELINTERFACES_H

#include "mvvm_global.h"
#include <QList>

class QStandardItem;

namespace ModelView {

class SessionItem;

//! Base class to construct row of QStandardItems from given SessionItem.

class CORE_EXPORT RowConstructorInterface
{
public:
    virtual ~RowConstructorInterface() = default;

    virtual QList<QStandardItem*> constructRow(SessionItem* item) = 0;
};

}  // namespace ModelView

#endif // MVVM_VIEWMODELINTERFACES_H
