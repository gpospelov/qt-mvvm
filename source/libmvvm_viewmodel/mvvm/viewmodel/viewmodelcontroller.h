// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_REFVIEWMODELCONTROLLER_H
#define MVVM_VIEWMODEL_REFVIEWMODELCONTROLLER_H

#include <memory>
#include <mvvm/core/export.h>
#include <mvvm/model/tagrow.h>
#include <vector>

class QStandardItem;

namespace ModelView
{

class SessionModel;
class SessionItem;
class ViewModelBase;
class RefViewItem;
class ChildrenStrategyInterface;
class RowStrategyInterface;

/*!
@class ViewModelController
@brief Propagates changes from SessionModel to its ViewModelBase.
*/

class CORE_EXPORT ViewModelController
{
public:
    ViewModelController(SessionModel* session_model, ViewModelBase* view_model);
    virtual ~ViewModelController();

    void setChildrenStrategy(std::unique_ptr<ChildrenStrategyInterface> children_strategy);

    void setRowStrategy(std::unique_ptr<RowStrategyInterface> row_strategy);

    SessionModel* sessionModel() const;

    void setRootSessionItem(SessionItem* item);

    SessionItem* rootSessionItem() const;

    std::vector<RefViewItem*> findViews(const ModelView::SessionItem* item) const;

protected:
    virtual void onDataChange(SessionItem* item, int role);
    virtual void onItemInserted(SessionItem* parent, TagRow tagrow);
    virtual void onItemRemoved(SessionItem* parent, TagRow tagrow);
    virtual void onAboutToRemoveItem(SessionItem* parent, TagRow tagrow);

    void update_branch(const SessionItem* item);

private:
    struct RefViewModelControllerImpl;
    std::unique_ptr<RefViewModelControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_REFVIEWMODELCONTROLLER_H
