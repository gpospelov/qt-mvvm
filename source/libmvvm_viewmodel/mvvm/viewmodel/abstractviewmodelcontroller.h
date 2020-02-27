// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_ABSTRACTVIEWMODELCONTROLLER_H
#define MVVM_VIEWMODEL_ABSTRACTVIEWMODELCONTROLLER_H

#include <mvvm/viewmodel/refviewmodelcontroller.h>

namespace ModelView
{
class CORE_EXPORT AbstractViewModelController : public RefViewModelController
{
public:
    AbstractViewModelController(SessionModel* session_model, ViewModelBase* view_model) : RefViewModelController(session_model, view_model){}

};
}

//#include <memory>
//#include <mvvm/core/export.h>
//#include <mvvm/model/tagrow.h>
//#include <string>

//class QStandardItem;

//namespace ModelView
//{

//class AbstractViewModel;
//class SessionItem;
//class ChildrenStrategyInterface;
//class RowStrategyInterface;
//class SessionModel;

///*!
//@class AbstractViewModelController
//@brief Propagates changes from SessionModel to its AbstractViewModel.
//*/

//class CORE_EXPORT AbstractViewModelController
//{
//public:
//    // FIXME refactor: make majority of methods private
//    explicit AbstractViewModelController(AbstractViewModel* view_model = nullptr);
//    virtual ~AbstractViewModelController();

//    void setViewModel(AbstractViewModel* view_model);

//    void setSessionModel(SessionModel* model);

//    void setChildrenStrategy(std::unique_ptr<ChildrenStrategyInterface> children_strategy);

//    void setRowStrategy(std::unique_ptr<RowStrategyInterface> row_strategy);

//    virtual void iterate(const SessionItem* item, QStandardItem* parent);

//    void init_view_model();

//    void setRootSessionItem(SessionItem* item);

//    SessionItem* rootSessionItem() const;

//    SessionModel* sessionModel();
//    const SessionModel* sessionModel() const;

//protected:
//    void check_initialization();

//    void generate_children_views(SessionItem* parent);
//    virtual void onDataChange(SessionItem* item, int role);
//    virtual void onItemInserted(SessionItem* parent, TagRow tagrow);
//    virtual void onItemRemoved(SessionItem* parent, TagRow tagrow);

//private:
//    struct AbstractViewModelControllerImpl;
//    std::unique_ptr<AbstractViewModelControllerImpl> p_impl;
//};

//} // namespace ModelView

#endif // MVVM_VIEWMODEL_ABSTRACTVIEWMODELCONTROLLER_H
