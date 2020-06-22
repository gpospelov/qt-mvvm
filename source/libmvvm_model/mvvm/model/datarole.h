// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_DATAROLE_H
#define MVVM_MODEL_DATAROLE_H

#include <QVariant>
#include <mvvm_model_export.h>

namespace ModelView
{

//! Represents pair of data,role for SessionItemData.

class MVVM_MODEL_EXPORT DataRole
{
public:
    DataRole(QVariant data = QVariant(), int role = -1);
    QVariant m_data;
    int m_role;
    bool operator==(const DataRole& other) const;
};

} // namespace ModelView

#endif // MVVM_MODEL_DATAROLE_H
