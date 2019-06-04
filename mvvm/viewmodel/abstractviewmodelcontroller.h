// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_ABSTRACTVIEWMODELCONTROLLER_H
#define MVVM_ABSTRACTVIEWMODELCONTROLLER_H

#include "mvvm_global.h"
#include <memory>
#include <vector>

class QStandardItem;
#include <QList>

namespace ModelView
{

class AbstractViewModel;
class SessionItem;
class ChildrenStrategyInterface;
class RowStrategyInterface;
class SessionModel;

/*!
@class AbstractViewModelController
@brief Propagates changes from SessionModel to its AbstractViewModel.
*/

class CORE_EXPORT AbstractViewModelController
{
public:
    AbstractViewModelController(AbstractViewModel* view_model);
    virtual ~AbstractViewModelController();

    void setSessionModel(SessionModel* model);

    void setChildrenStrategy(std::unique_ptr<ChildrenStrategyInterface> children_strategy);

    void setRowStrategy(std::unique_ptr<RowStrategyInterface> row_strategy);

    void reset_view_model();

    virtual void iterate(const SessionItem* item, QStandardItem* parent);

    void init_view_model();

    void setRootSessionItem(SessionItem* item);

    SessionItem* rootSessionItem() const;

    SessionModel* sessionModel();
    const SessionModel* sessionModel() const;

    virtual void generate_children_views(SessionItem* parent);

    virtual void onDataChange(SessionItem* item, int role);
    virtual void onRowInserted(SessionItem* parent, std::string tag, int row);
    virtual void onRowRemoved(SessionItem* parent, std::string tag, int row);

private:
    class AbstractViewModelControllerPrivate;
    std::unique_ptr<AbstractViewModelControllerPrivate> p_impl;
};

} // namespace ModelView

#endif // MVVM_ABSTRACTVIEWMODELCONTROLLER_H
