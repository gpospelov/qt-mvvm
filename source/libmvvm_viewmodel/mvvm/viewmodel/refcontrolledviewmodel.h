// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_REFCONTROLLEDVIEWMODEL_H
#define MVVM_VIEWMODEL_REFCONTROLLEDVIEWMODEL_H

#include <memory>
#include <mvvm/core/export.h>
#include <mvvm/viewmodel/refviewmodel.h>

namespace ModelView
{

class SessionModel;
class SessionItem;
class RefViewItem;
class RefViewModelController;

//!

class CORE_EXPORT RefControlledViewModel : public RefViewModel
{
public:
    RefControlledViewModel(std::unique_ptr<RefViewModelController> controller,
                           QObject* parent = nullptr);
    ~RefControlledViewModel() override;

    SessionModel* sessionModel() const;

    SessionItem* rootSessionItem();

    void setRootSessionItem(SessionItem* item);

    SessionItem* sessionItemFromIndex(const QModelIndex& index) const;

    RefViewItem* viewItemFromIndex(const QModelIndex& index) const;

    QModelIndexList indexOfSessionItem(const SessionItem* item) const;

    std::vector<RefViewItem*> findViews(const ModelView::SessionItem* item) const;

private:
    std::unique_ptr<RefViewModelController> m_controller;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_REFCONTROLLEDVIEWMODEL_H
