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
const model_type ViewportAxisType = "ViewportAxis";
const model_type FixedBinAxisType = "FixedBinAxis";
const model_type Data1DItemType = "Data1DItem";
const model_type Data2DItemType = "Data2DItem";
const model_type GraphItemType = "GraphItem";
const model_type GraphViewportItemType = "GraphViewportItem";
const model_type TextType = "Text";
const model_type ContainerType = "Container";
} // namespace Constants

} // namespace ModelView

#endif // MVVM_MVVM_TYPES_H

