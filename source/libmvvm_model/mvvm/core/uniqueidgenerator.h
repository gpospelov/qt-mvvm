// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_UNIQUEIDGENERATOR_H
#define MVVM_MODEL_UNIQUEIDGENERATOR_H

#include <mvvm/core/types.h>
#include <mvvm/model_export.h>

namespace ModelView
{

/*!
@class UniqueIdGenerator
@brief Provides generation of unique SessionItem itentifier.

In the future might be turned to singleton to keep track of all generated identifier
and make sure, that SessionItem identifiers loaded from disk, are different from those
generated during dynamic session. For the moment though, we rely on zero-probability of
such event.
*/

class MVVM_MODEL_EXPORT UniqueIdGenerator
{
public:
    static identifier_type generate();
};

} // namespace ModelView

#endif // MVVM_MODEL_UNIQUEIDGENERATOR_H
