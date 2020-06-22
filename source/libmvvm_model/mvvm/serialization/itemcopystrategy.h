// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_ITEMCOPYSTRATEGY_H
#define MVVM_SERIALIZATION_ITEMCOPYSTRATEGY_H

#include <memory>
#include <mvvm/core/export.h>

namespace ModelView
{

class SessionItem;

//! Interface to copy items within context.

class MVVM_MODEL_EXPORT ItemCopyStrategy
{
public:
    virtual ~ItemCopyStrategy() = default;

    //! Creates item copy by deep copying all children. SessionItem identifiers will be regenerated.
    virtual std::unique_ptr<SessionItem> createCopy(const SessionItem* item) const = 0;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_ITEMCOPYSTRATEGY_H
