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

class QStandardItem;

namespace ModelView
{

class SessionModel;
class ViewModel;
class ChildrenStrategyInterface;
class RowStrategyInterface;

/*!
@class RefViewModelController
@brief Propagates changes from SessionModel to its ViewModel.
*/

class CORE_EXPORT RefViewModelController
{
public:
    RefViewModelController(SessionModel* session_model, ViewModel* view_model);
    virtual ~RefViewModelController();

    void setChildrenStrategy(std::unique_ptr<ChildrenStrategyInterface> children_strategy);

    void setRowStrategy(std::unique_ptr<RowStrategyInterface> row_strategy);


    SessionModel* sessionModel() const;


private:
    struct RefViewModelControllerImpl;
    std::unique_ptr<RefViewModelControllerImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_REFVIEWMODELCONTROLLER_H
