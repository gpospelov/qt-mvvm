// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef VECTORITEM_H
#define VECTORITEM_H

#include "compounditem.h"

namespace ModelView {

//! Vector item with three x,y,z property items.

class CORE_EXPORT VectorItem : public CompoundItem
{
public:
    static const std::string P_X;
    static const std::string P_Y;
    static const std::string P_Z;

    VectorItem();
};

} // ModelView

#endif // VECTORITEM_H


