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
const int APPEARANCE = 4;
};

enum Appearance {
    NOFLAGS = 0x000,
    ENABLED = 0x001,
    EDITABLE = 0x002
};

namespace Constants {
const model_type BaseType = "SessionItem";
const model_type PropertyType = "Property";
const model_type CompoundType = "Compound";
const model_type VectorType = "Vector";
} // namespace Constants

namespace Callbacks {
using client_t = const void*;
using item_t = std::function<void(SessionItem*)>;
using item_int_t = std::function<void(SessionItem*, int)>;
using item_str_t = std::function<void(SessionItem*, std::string)>;
using item_int_str_t = std::function<void(SessionItem*, int, std::string)>;
}

} // namespace ModelView

#endif
