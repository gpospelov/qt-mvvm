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

namespace ModelView
{

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

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;

    QModelIndex parent(const QModelIndex &child) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

}; // namespace ModelView

#endif // MVVM_VIEWMODEL_REFVIEWMODEL_H
