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

#include <QAbstractItemModel>
#include <memory>
#include <mvvm/core/export.h>

namespace ModelView
{

class RefViewItem;

/*!
@class ViewModelBase
@brief Base class for all view models to show content of SessionModel in Qt views.

ViewModelBase is made of ViewItems, where each ViewItem represents some concrete data role
of SessionItem. ViewModelBase dosn't have own logic and needs ViewModelController to listen for
SessionModel changes.
*/

class CORE_EXPORT ViewModelBase : public QAbstractItemModel
{
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

    RefViewItem* rootItem() const;

    RefViewItem* itemFromIndex(const QModelIndex& index) const;

    QModelIndex indexFromItem(const RefViewItem* item) const;

    void removeRow(RefViewItem* parent, int row);

    void clearRows(RefViewItem* parent);

    void insertRow(RefViewItem* parent, int row, std::vector<std::unique_ptr<RefViewItem>> items);

    void appendRow(RefViewItem* parent, std::vector<std::unique_ptr<RefViewItem>> items);

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void setRootViewItem(std::unique_ptr<RefViewItem> root_item);

private:
    struct RefViewModelImpl;
    std::unique_ptr<RefViewModelImpl> p_impl;
};

}; // namespace ModelView

#endif // MVVM_VIEWMODEL_VIEWMODELBASE_H