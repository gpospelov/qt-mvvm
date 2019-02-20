// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MODELTYPES_H
#define MODELTYPES_H

#include <string>
#include <functional>

namespace ModelView {

class SessionItem;

using identifier_type = std::string;
using model_type = std::string;

//! Defines constants to be used as SessionItem data role.

namespace ItemDataRole {
const int IDENTIFIER = 0;
const int DATA = 1;
const int DISPLAY = 2;
const int DEFAULT_TAG = 3;
};

namespace Constants {
const model_type PropertyType = "Property";
const model_type CompoundType = "Compound";
} // namespace Constants

namespace Callbacks {
using caller_t = const void*;
using func_item_t = std::function<void(SessionItem*)>;
using func_item_int_t = std::function<void(SessionItem*, int)>;
using func_item_int_str_t = std::function<void(SessionItem*, int, std::string)>;
}

} // namespace ModelView

#endif
