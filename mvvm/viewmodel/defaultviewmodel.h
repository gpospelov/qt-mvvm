// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_DEFAULTVIEWMODEL_H
#define MVVM_DEFAULTVIEWMODEL_H

#include "abstractviewmodel.h"
#include <memory>
#include <vector>

namespace ModelView
{

class ViewItem;
class RowConstructorInterface;
class ChildrenStrategyInterface;


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

class CORE_EXPORT DefaultViewModel : public AbstractViewModel
{
public:
    DefaultViewModel(QObject* parent = nullptr);
    DefaultViewModel(SessionModel* model, QObject* parent = nullptr);
    ~DefaultViewModel() override;

protected:
    void setRowConstructor(std::unique_ptr<RowConstructorInterface> row_constructor);
    void setChildrenStrategy(std::unique_ptr<ChildrenStrategyInterface> children_strategy);

    void init_view_model() override;
    void onDataChange(SessionItem* item, int role) override;
    void onRowInserted(SessionItem* parent, std::string tag, int row) override;
    void onRowRemoved(SessionItem* parent, std::string tag, int row) override;
    void onModelReset() override;

    void generate_children_views(SessionItem* parent);

    void update_model();
    virtual void iterate(const SessionItem* item, QStandardItem* parent);
    virtual std::vector<SessionItem*> item_children(const SessionItem* item) const;

    std::unique_ptr<RowConstructorInterface> m_row_constructor;
    std::unique_ptr<ChildrenStrategyInterface> m_children_strategy;
};

} // namespace ModelView

#endif // MVVM_DEFAULTVIEWMODEL_H
