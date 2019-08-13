// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_MVVM_TYPES_H
#define MVVM_MVVM_TYPES_H

#include <string>
#include <functional>

namespace ModelView {

class SessionItem;
class SessionModel;

using identifier_type = std::string;
using model_type = std::string;

//! Defines constants to be used as SessionItem data role.

namespace ItemDataRole {
const int IDENTIFIER = 0;
const int DATA = 1;
const int DISPLAY = 2;
const int APPEARANCE = 3;
const int LIMITS = 4;
};

enum Appearance {
    NOFLAGS = 0x000,
    ENABLED = 0x001,
    EDITABLE = 0x002
};

namespace Constants {
const model_type BaseType = "SessionItem";
const model_type PropertyType = "Property";
const model_type GroupType = "Group";
const model_type CompoundType = "Compound";
const model_type VectorType = "Vector";
const model_type LinkedType = "Linked";
const model_type FixedBinAxisType = "FixedBinAxis";
const model_type Data1DItemType = "Data1DItem";
const model_type GraphItemType = "GraphItem";
} // namespace Constants

namespace Callbacks {
using client_t = const void*;
using item_t = std::function<void(SessionItem*)>;
using item_int_t = std::function<void(SessionItem*, int)>;
using item_str_t = std::function<void(SessionItem*, std::string)>;
using item_str_int_t = std::function<void(SessionItem*, std::string, int)>;
using model_t = std::function<void(SessionModel*)>;
}

} // namespace ModelView

#endif // MVVM_MVVM_TYPES_H

