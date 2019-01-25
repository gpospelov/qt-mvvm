// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef COMPOUNDITEM_H
#define COMPOUNDITEM_H

#include "sessionitem.h"

namespace ModelView {

//! Complex item holding mixed SessionItem types (properties, other

class CORE_EXPORT CompoundItem : public SessionItem
{
public:
    CompoundItem();

    SessionItem* addProperty(const std::string& name, const QVariant& variant);

};

} // namespace ModelView

#endif // COMPOUNDITEM_H
