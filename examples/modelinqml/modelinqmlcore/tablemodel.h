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

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    int rowCount(const QModelIndex& = QModelIndex()) const override
    {
        return m_data.size();
    }

    int columnCount(const QModelIndex& = QModelIndex()) const override
    {
        return m_data[0].size();
    }

    QVariant data(const QModelIndex& index, int role) const override
    {
        switch (role) {
        case Qt::DisplayRole:
            return m_data[index.row()][index.column()];
        default:
            break;
        }

        return QVariant();
    }

    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override
    {
        if (!index.isValid() || role != Qt::EditRole)
            return false;
        if (m_data[index.row()][index.column()] == value .toString())
            return false;

        m_data[index.row()][index.column()] = value.toString();
        emit(dataChanged(index, index));

        return true;
    }

    /*
    QHash<int, QByteArray> roleNames() const override
    {
        return {
            {Qt::DisplayRole, "display"},
            {Qt::EditRole, "edit"}
        };
    }
    */

private:
    QList<QStringList> m_data = {
        { "one", "two", "three" },
        { "1", "2", "3"},
        { "7", "9", "2"},
        { "C", "B", "A"}
    };

};

#endif // MODELINQMLCORE_TABLEMODEL_H
