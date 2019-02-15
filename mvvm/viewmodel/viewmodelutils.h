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
#include <QVector>

class QStandardItemModel;
class QStandardItem;
class QModelIndex;

namespace ModelView {

class ViewItem;
class SessionItem;

namespace Utils {

//! Iterates through QStandardItem model
CORE_EXPORT void iterate_model(const QStandardItemModel* model, const QModelIndex& parent, std::function<void(QStandardItem*)> fun);

//! Returns vector of all ViewItems from the model representing given SessionItem.
CORE_EXPORT std::vector<ViewItem*> findViews(const QStandardItemModel* model, const QModelIndex& parent, SessionItem* item);

//! Returns vector of Qt roles corresponding to given ItemDataRole.
CORE_EXPORT QVector<int> item_role_to_qt(int role);

} // Utils

} // ModelView

#endif // VIEWMODELUTILS_H
