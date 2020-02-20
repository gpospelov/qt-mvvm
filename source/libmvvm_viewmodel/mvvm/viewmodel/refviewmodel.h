// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_VIEWMODEL_REFVIEWMODEL_H
#define MVVM_VIEWMODEL_REFVIEWMODEL_H

#include <QAbstractItemModel>
#include <mvvm/core/export.h>
#include <memory>

namespace ModelView
{

class RefViewItem;

/*!
@class RefViewModel
@brief Base class for all view models to show content of SessionModel in Qt views.

ViewModel is made of ViewItems, where each ViewItem represents some concrete data role
of SessionItem.
*/

class CORE_EXPORT RefViewModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit RefViewModel(QObject* parent = nullptr);
    ~RefViewModel() override;

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;

    QModelIndex parent(const QModelIndex &child) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex& index, const QVariant& value, int role) override;

    RefViewItem* rootItem() const;

    RefViewItem* itemFromIndex(const QModelIndex& index) const;

    QModelIndex indexFromItem(const RefViewItem *item) const;

    void removeRow(RefViewItem* parent, int row);

    void insertRow(RefViewItem* parent, int row, std::vector<std::unique_ptr<RefViewItem>> items);

    void appendRow(RefViewItem* parent, std::vector<std::unique_ptr<RefViewItem>> items);

private:
    struct RefViewModelImpl;
    std::unique_ptr<RefViewModelImpl> p_impl;
};

}; // namespace ModelView

#endif // MVVM_VIEWMODEL_REFVIEWMODEL_H
