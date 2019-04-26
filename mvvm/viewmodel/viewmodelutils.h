// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODELUTILS_H
#define MVVM_VIEWMODELUTILS_H

#include "mvvm_global.h"
#include <QVariant>
#include <QVector>
#include <functional>
#include <vector>

class QStandardItemModel;
class QStandardItem;
class QModelIndex;

namespace ModelView
{

class ViewItem;
class SessionItem;

namespace Utils
{

//! Iterates through QStandardItem model
CORE_EXPORT void iterate_model(const QStandardItemModel* model, const QModelIndex& parent,
                               std::function<void(QStandardItem*)> fun);

//! Returns vector of all ViewItems from the model representing given SessionItem.
CORE_EXPORT std::vector<ViewItem*> findViews(const QStandardItemModel* model,
                                             const QModelIndex& parent, const SessionItem* item);

//! Returns vector of Qt roles corresponding to given ItemDataRole.
CORE_EXPORT QVector<int> item_role_to_qt(int role);

//! Returns text color for given item.
CORE_EXPORT QVariant TextColorRole(const SessionItem& item);

//! Returns check state role of given item.
CORE_EXPORT QVariant CheckStateRole(const SessionItem& item);

//! Returns decoration role for given item.
CORE_EXPORT QVariant DecorationRole(const SessionItem& item);

} // namespace Utils

} // namespace ModelView

#endif // MVVM_VIEWMODELUTILS_H
