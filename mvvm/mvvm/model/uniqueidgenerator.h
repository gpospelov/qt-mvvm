// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_UNIQUEIDGENERATOR_H
#define MVVM_UNIQUEIDGENERATOR_H

#include "mvvm_export.h"
#include "mvvm_types.h"

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

class CORE_EXPORT UniqueIdGenerator
{
public:
    static identifier_type generate();
};

} // namespace ModelView

#endif //  MVVM_UNIQUEIDGENERATOR_H
