// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef DEFAULTVIEWMODEL_H
#define DEFAULTVIEWMODEL_H

#include "viewmodel.h"
#include <vector>
#include <memory>

namespace ModelView {

class ViewItem;
class RowConstructorInterface;

//! The view model to show content of SessionModel in Qt views.
//!
//! DefaultViewModel is connected with SessionModel and notifies views on SessionItem's
//! insert/remove/data change. The data change in a view will be propagated back to SessionModel.
//!
//! Important limitation: DefaultViewModel is not intended for insert/remove through
//! QStandardItemModel interface. Everything should be done throught SessionModel.
//!
//! Important feature: DefaultViewModel doesn't care about correct removal of QStandardItemModel
//! rows and columns. Every time the row of parent SessionItem is removed, DefaultViewModel
//! removes _all_ children of corresponding ViewItem and then rebuild whole branch.

class CORE_EXPORT DefaultViewModel : public ViewModel {
public:
    DefaultViewModel(QObject* parent = nullptr);
    ~DefaultViewModel() override;

    std::vector<ViewItem*> findViews(SessionItem* item);

private:
    void init_view_model() override;
    void onDataChange(SessionItem* item, int role) override;
    void onRowInserted(SessionItem* parent, int row) override;
    void onRowRemoved(SessionItem* parent, int row, std::string id) override;

    void update_model();
    void iterate(SessionItem* item, QStandardItem* parent);

    std::unique_ptr<RowConstructorInterface> m_row_constructor;
};

}  // namespace ModelView

#endif // VIEWMODEL_H
