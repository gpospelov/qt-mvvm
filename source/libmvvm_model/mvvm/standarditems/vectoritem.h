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

#include "mvvm/model/compounditem.h"

namespace ModelView {

//! Vector item with three x,y,z property items.

class MVVM_MODEL_EXPORT VectorItem : public CompoundItem {
public:
    static inline const std::string P_X = "P_X";
    static inline const std::string P_Y = "P_Y";
    static inline const std::string P_Z = "P_Z";

    VectorItem();

    void activate() override;

    double x() const;
    void setX(double value);

    double y() const;
    void setY(double value);

    double z() const;
    void setZ(double value);

private:
    void update_label();
};

} // namespace ModelView

#endif // MVVM_STANDARDITEMS_VECTORITEM_H
