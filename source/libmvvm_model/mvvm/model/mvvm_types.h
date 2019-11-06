// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_MODEL_MVVM_TYPES_H
#define MVVM_MODEL_MVVM_TYPES_H

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
const model_type GroupItemType = "Group";
const model_type CompoundItemType = "Compound";
const model_type VectorItemType = "Vector";
const model_type LinkedItemType = "Linked";
const model_type ViewportAxisItemType = "ViewportAxis";
const model_type FixedBinAxisItemType = "FixedBinAxis";
const model_type Data1DItemType = "Data1D";
const model_type Data2DItemType = "Data2D";
const model_type GraphItemType = "Graph";
const model_type GraphViewportItemType = "GraphViewport";
const model_type TextItemType = "Text";
const model_type ContainerItemType = "Container";
const model_type ColorMapItemType = "ColorMap";
const model_type ColorMapViewportItemType = "ColorMapViewport";
} // namespace Constants

} // namespace ModelView

#endif  // MVVM_MODEL_MVVM_TYPES_H

