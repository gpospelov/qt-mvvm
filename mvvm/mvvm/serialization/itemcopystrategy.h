// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_ITEMCOPYSTRATEGY_H
#define MVVM_ITEMCOPYSTRATEGY_H

#include <mvvm/model/mvvm_export.h>
#include <memory>

namespace ModelView
{

class SessionItem;

//! Interface to copy items within context.

class CORE_EXPORT ItemCopyStrategy
{
public:
    virtual ~ItemCopyStrategy() = default;

    //! Creates item copy by deep copying all children. SessionItem identifiers will be regenerated.
    virtual std::unique_ptr<SessionItem> createCopy(const SessionItem* item) const = 0;
};

} // namespace ModelView

#endif // MVVM_ITEMCOPYSTRATEGY_H
