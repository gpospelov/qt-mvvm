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
#include <vector>

class QStandardItemModel;
class QStandardItem;
class QModelIndex;

namespace ModelView {

class ViewItem;
class SessionItem;

//! Iterates through QStandardItem model
CORE_EXPORT void iterate_model(const QStandardItemModel* model, const QModelIndex& parent, std::function<void(QStandardItem*)> fun);

//! Returns vector of all ViewItems from the model.
CORE_EXPORT std::vector<ViewItem*> findViews(const QStandardItemModel* model, const QModelIndex& parent, SessionItem* item);

} // VIEWMODELUTILS_H

#endif // VIEWMODELUTILS_H
