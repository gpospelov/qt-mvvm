// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_VIEWMODEL_H
#define MVVM_VIEWMODEL_VIEWMODEL_H

#include "mvvm/viewmodel/viewmodelbase.h"

namespace ModelView {

class SessionModel;
class SessionItem;
class ViewItem;
class ViewModelController;

//! Main class to represent content of SessionModel in Qt's trees and tables.

class MVVM_VIEWMODEL_EXPORT ViewModel : public ViewModelBase {
    Q_OBJECT

public:
    ViewModel(std::unique_ptr<ViewModelController> controller, QObject* parent = nullptr);
    ~ViewModel() override;

    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    SessionModel* sessionModel() const;

    SessionItem* rootSessionItem();

    void setRootSessionItem(SessionItem* item);

    SessionItem* sessionItemFromIndex(const QModelIndex& index) const;

    ViewItem* viewItemFromIndex(const QModelIndex& index) const;

    QModelIndexList indexOfSessionItem(const SessionItem* item) const;

    std::vector<ViewItem*> findViews(const ModelView::SessionItem* item) const;

private:
    std::unique_ptr<ViewModelController> m_controller;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_VIEWMODEL_H
