// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef VIEWMODELUTILS_H
#define VIEWMODELUTILS_H

#include "global.h"
#include <functional>

class QStandardItemModel;
class QStandardItem;
class QModelIndex;

namespace ModelView {

//! Iterates through QStandardItem model
CORE_EXPORT void iterate_model(const QStandardItemModel* model, const QModelIndex& parent, std::function<void(const QStandardItem*)> fun);

} // VIEWMODELUTILS_H

#endif // VIEWMODELUTILS_H
