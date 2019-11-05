// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_SESSIONITEMDATA_H
#define MVVM_SESSIONITEMDATA_H

#include <mvvm/model/mvvm_export.h>
#include <mvvm/model/datarole.h>
#include <QVariant>
#include <vector>

namespace ModelView
{

//! Handles data roles for SessionItem.

class CORE_EXPORT SessionItemData
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
    void assure_validity(const QVariant& variant, int role);
    container_type m_values;
};

} // namespace ModelView

#endif // MVVM_SESSIONITEMDATA_H

