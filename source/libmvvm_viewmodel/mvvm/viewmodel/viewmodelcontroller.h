// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_VIEWMODELCONTROLLER_H
#define MVVM_VIEWMODEL_VIEWMODELCONTROLLER_H

#include "mvvm/signals/modellistener.h"
#include "mvvm/viewmodel_export.h"
#include <QStringList>
#include <memory>
#include <vector>

namespace ModelView {

class SessionModel;
class SessionItem;
class ViewModelBase;
class ViewItem;
class ChildrenStrategyInterface;
class RowStrategyInterface;

//! Propagates changes from SessionModel to its ViewModelBase.

class MVVM_VIEWMODEL_EXPORT ViewModelController : public ModelListener<SessionModel> {
public:
    ViewModelController(SessionModel* session_model, ViewModelBase* view_model = nullptr);
    ~ViewModelController();

    void setViewModel(ViewModelBase* view_model);

    void setChildrenStrategy(std::unique_ptr<ChildrenStrategyInterface> children_strategy);

    void setRowStrategy(std::unique_ptr<RowStrategyInterface> row_strategy);

    SessionModel* sessionModel() const;

    void setRootSessionItem(SessionItem* item);

    SessionItem* rootSessionItem() const;

    std::vector<ViewItem*> findViews(const ModelView::SessionItem* item) const;

    QStringList horizontalHeaderLabels() const;

protected:
    virtual void onDataChange(SessionItem* item, int role);
    virtual void onItemInserted(SessionItem* parent, TagRow tagrow);
    virtual void onItemRemoved(SessionItem* parent, TagRow tagrow);
    virtual void onAboutToRemoveItem(SessionItem* parent, TagRow tagrow);

    void update_branch(const SessionItem* item);

private:
    struct ViewModelControllerImpl;
    std::unique_ptr<ViewModelControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_VIEWMODELCONTROLLER_H
