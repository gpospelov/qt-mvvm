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
#include <memory>
#include <QStandardItemModel>

class QStandardItem;

namespace ModelView
{

class SessionModel;
class SessionItem;
class ViewItem;
class RowConstructorInterface;
class ChildrenStrategyInterface;

//! Base class for all view models to show content of  SessionModel in Qt views.

//! The view model to show content of SessionModel in Qt views.
//!
//! DefaultViewModel is connected with SessionModel and notifies views on SessionItem's
//! insert/remove/data change. The data change in a view will be propagated back to SessionModel.
//!
//! Important limitation: DefaultViewModel is not intended for insert/remove through
//! QStandardItemModel interface. Everything should be done through SessionModel.
//!
//! Important feature: DefaultViewModel doesn't care about correct removal of QStandardItemModel
//! rows and columns. Every time the row of parent SessionItem is removed, DefaultViewModel
//! removes _all_ children of corresponding ViewItem and then rebuild whole branch.

class CORE_EXPORT AbstractViewModel : public QStandardItemModel
{
public:
    AbstractViewModel(QObject* parent = nullptr);
    virtual ~AbstractViewModel();

    void setSessionModel(SessionModel* model);

    std::vector<ViewItem*> findViews(const SessionItem* item) const;

    SessionItem* sessionItemFromIndex(const QModelIndex& index) const;

    QModelIndexList indexOfSessionItem(const SessionItem* item) const;

    void setRootSessionItem(SessionItem* item);

protected:
    SessionItem* rootSessionItem() const;
    QStandardItem* rootViewItem() const;

    std::vector<QStandardItem*> findStandardViews(const SessionItem* item) const;

protected:
    void setRowConstructor(std::unique_ptr<RowConstructorInterface> row_constructor);
    void setChildrenStrategy(std::unique_ptr<ChildrenStrategyInterface> children_strategy);

    virtual void init_view_model();
    virtual void onDataChange(SessionItem* item, int role);
    virtual void onRowInserted(SessionItem* parent, std::string tag, int row);
    virtual void onRowRemoved(SessionItem* parent, std::string tag, int row);
    virtual void onModelReset();
    virtual void update_model(){}

    std::unique_ptr<RowConstructorInterface> m_row_constructor;
    std::unique_ptr<ChildrenStrategyInterface> m_children_strategy;

    SessionModel* m_sessionModel;
    SessionItem* m_rootItem;
};

} // namespace ModelView

#endif // MVVM_ABSTRACTVIEWMODEL_H
