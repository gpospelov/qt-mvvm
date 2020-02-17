// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <mvvm/viewmodel/refviewmodel.h>

using namespace ModelView;

RefViewModel::RefViewModel(QObject* parent) : QAbstractItemModel(parent) {}

QModelIndex RefViewModel::index(int row, int column, const QModelIndex& parent) const
{
    Q_UNUSED(row)
    Q_UNUSED(column)
    Q_UNUSED(parent)
    return QModelIndex();
}

QModelIndex RefViewModel::parent(const QModelIndex& child) const
{
    Q_UNUSED(child)
    return QModelIndex();
}

int RefViewModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 0;
}

int RefViewModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent)
    return 0;
}

QVariant RefViewModel::data(const QModelIndex& index, int role) const
{
    Q_UNUSED(index)
    Q_UNUSED(role)
    return QVariant();
}
