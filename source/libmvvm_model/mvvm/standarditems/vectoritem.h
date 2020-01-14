// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_STANDARDITEMS_VECTORITEM_H
#define MVVM_STANDARDITEMS_VECTORITEM_H

#include <mvvm/model/compounditem.h>

namespace ModelView
{

//! Vector item with three x,y,z property items.

class CORE_EXPORT VectorItem : public CompoundItem
{
public:
    static const std::string P_X;
    static const std::string P_Y;
    static const std::string P_Z;

    VectorItem();

    void activate() override;

private:
    void update_label();
};

} // namespace ModelView

#endif // MVVM_STANDARDITEMS_VECTORITEM_H
