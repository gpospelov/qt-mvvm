// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_VIEWMODELUTILS_H
#define MVVM_VIEWMODEL_VIEWMODELUTILS_H

#include <mvvm/core/export.h>
#include <functional>
#include <vector>
#include <QVector>
#include <QModelIndex>
#include <QModelIndexList>

class QStandardItemModel;
class QStandardItem;
class QVariant;

namespace ModelView
{

class ViewItem;
class SessionItem;

namespace Utils
{

//! Iterates through QStandardItem model
CORE_EXPORT void iterate_model(const QStandardItemModel* model, const QModelIndex& parent,
                               std::function<void(QStandardItem*)> fun);

//! Returns vector of all ViewItems representing given SessionItem.
CORE_EXPORT std::vector<ViewItem*> findViews(const QStandardItemModel* model,
                                             const SessionItem* item,
                                             const QModelIndex& parent = QModelIndex());

//! Returns vector of Qt roles corresponding to given ItemDataRole.
CORE_EXPORT QVector<int> item_role_to_qt(int role);

//! Returns text color for given item.
CORE_EXPORT QVariant TextColorRole(const SessionItem& item);

//! Returns check state role of given item.
CORE_EXPORT QVariant CheckStateRole(const SessionItem& item);

//! Returns decoration role for given item.
CORE_EXPORT QVariant DecorationRole(const SessionItem& item);

//! Returns vector of parent items from given index list.
//! Finds all SessionItems corresponding to given index list and collect their parents.
//! Function is usefull in the context of table-like views when we want to find compound items
//! (i.e. Layers) from table cells containing LayerItem's properties (i.e. thickness).
CORE_EXPORT std::vector<SessionItem*> ParentItemsFromIndex(const QModelIndexList& index_list);

} // namespace Utils

} // namespace ModelView

#endif  // MVVM_VIEWMODEL_VIEWMODELUTILS_H
