// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_VIEWMODELBASE_H
#define MVVM_VIEWMODEL_VIEWMODELBASE_H

#include "mvvm/viewmodel_export.h"
#include <QAbstractItemModel>
#include <memory>

namespace ModelView {

class ViewItem;

//! Base class for all view models to show content of SessionModel in Qt views.
//! ViewModelBase is made of ViewItems, where each ViewItem represents some concrete data role
//! of SessionItem. ViewModelBase doesn't have own logic and needs ViewModelController to listen
//! for SessionModel changes.

class MVVM_VIEWMODEL_EXPORT ViewModelBase : public QAbstractItemModel {
    Q_OBJECT

public:
    explicit ViewModelBase(QObject* parent = nullptr);
    ~ViewModelBase() override;

    QModelIndex index(int row, int column,
                      const QModelIndex& parent = QModelIndex()) const override;

    QModelIndex parent(const QModelIndex& child) const override;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex& index, const QVariant& value, int role) override;

    ViewItem* rootItem() const;

    ViewItem* itemFromIndex(const QModelIndex& index) const;

    QModelIndex indexFromItem(const ViewItem* item) const;

    void removeRow(ViewItem* parent, int row);

    void clearRows(ViewItem* parent);

    virtual void insertRow(ViewItem* parent, int row, std::vector<std::unique_ptr<ViewItem>> items);

    void appendRow(ViewItem* parent, std::vector<std::unique_ptr<ViewItem>> items);

    Qt::ItemFlags flags(const QModelIndex& index) const override;

private:
    void setRootViewItem(std::unique_ptr<ViewItem> root_item);
    friend class ViewModelController;
    struct ViewModelBaseImpl;
    std::unique_ptr<ViewModelBaseImpl> p_impl;
};

} // namespace ModelView

#endif // MVVM_VIEWMODEL_VIEWMODELBASE_H
