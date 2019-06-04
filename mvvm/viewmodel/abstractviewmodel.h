// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_ABSTRACTVIEWMODEL_H
#define MVVM_ABSTRACTVIEWMODEL_H

#include "mvvm_global.h"
#include <QStandardItemModel>
#include <memory>

class QStandardItem;

namespace ModelView
{

class SessionModel;
class SessionItem;
class ViewItem;
class RowConstructorInterface;
class ChildrenStrategyInterface;
class AbstractViewModelController;

/*!
@class AbstractViewModel
@brief Base class for all view models to show content of SessionModel in Qt views.

AbstractViewModel is just a QStandardItemModel connected with SessionModel. On every
insert/remove/data change in original SessionModel, AbstractViewModel gets notified
and updates its content.

Important details:

AbstractViewModel is made of ViewItems, where each ViewItem represents some concrete data role
of SessionItem.

AbstractViewModel is not intended for insert/remove through QStandardItemModel interface.
Everything should be done through SessionModel.

AbstractViewModel uses simplified mechanism of syncronization with SessionModel.
Every time some SessionItem is removed from SessionModel, in ViewModel we remove corersponding
ViewItem _together_ with all its siblings, and then regenerate corresponding parent's branch.
*/

class CORE_EXPORT AbstractViewModel : public QStandardItemModel
{
public:
    friend class AbstractViewModelController;
    AbstractViewModel(QObject* parent = nullptr);
    AbstractViewModel(std::unique_ptr<AbstractViewModelController> controller, QObject* parent = nullptr);
    virtual ~AbstractViewModel();

    void setSessionModel(SessionModel* model);

    SessionItem* sessionItemFromIndex(const QModelIndex& index) const;

    QModelIndexList indexOfSessionItem(const SessionItem* item) const;

    void setRootSessionItem(SessionItem* item);

    void setRowConstructor(std::unique_ptr<RowConstructorInterface> row_constructor);
    void setChildrenStrategy(std::unique_ptr<ChildrenStrategyInterface> children_strategy);

protected:
    QStandardItem* rootViewItem() const;

private:
    std::vector<QStandardItem*> findStandardViews(const SessionItem* item) const;
    std::vector<ViewItem*> findViews(const SessionItem* item) const;

    std::unique_ptr<AbstractViewModelController> m_controller;
};

} // namespace ModelView

#endif // MVVM_ABSTRACTVIEWMODEL_H
