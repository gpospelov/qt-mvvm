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
#include <vector>
#include "datarole.h"

//! Handles data roles for SessionItem.

class SessionItemData
{
public:
    using container_type = std::vector<DataRole>;
    using const_iterator = container_type::const_iterator;

    std::vector<int> roles() const;

    QVariant data(int role) const;

    bool setData(const QVariant& value, int role);

    const_iterator begin() const;
    const_iterator end() const;

private:
    container_type m_values;
};

#endif
