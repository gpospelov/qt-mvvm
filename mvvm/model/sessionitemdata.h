// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef SESSIONITEMDATA_H
#define SESSIONITEMDATA_H

#include <QVariant>
#include <QVector>

//! Handles data roles for SessionItem.

class SessionItemData
{
public:
    QVector<int> roles() const;

    QVariant data(int role) const;

    bool setData(const QVariant& value, int role);

private:
    class DataRole
    {
    public:
        DataRole(const QVariant& data = QVariant(), int role = -1);
        QVariant m_data;
        int m_role;
        bool operator==(const DataRole& other) const;
    };

    QVector<DataRole> m_values;
};

#endif
