// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MODELINQMLCORE_TABLEMODEL_H
#define MODELINQMLCORE_TABLEMODEL_H

#include <QAbstractTableModel>
#include <qqml.h>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    int rowCount(const QModelIndex& = QModelIndex()) const override { return 200; }

    int columnCount(const QModelIndex& = QModelIndex()) const override { return 200; }

    QVariant data(const QModelIndex& index, int role) const override
    {
        switch (role) {
        case Qt::DisplayRole:
            return QString("%1, %2").arg(index.column()).arg(index.row());
        default:
            break;
        }

        return QVariant();
    }

    QHash<int, QByteArray> roleNames() const override { return {{Qt::DisplayRole, "display"}}; }
};

#endif // MODELINQMLCORE_TABLEMODEL_H
