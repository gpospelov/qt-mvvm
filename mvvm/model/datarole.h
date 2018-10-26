// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef DATAROLE_H
#define DATAROLE_H

#include "global.h"
#include <QVariant>

namespace ModelView {

//! Represents pair of data,role for SessionItemData.

class CORE_EXPORT DataRole
{
public:
    DataRole(QVariant data = QVariant(), int role = -1);
    QVariant m_data;
    int m_role;
    bool operator==(const DataRole& other) const;
};

}  // namespace ModelView

#endif
