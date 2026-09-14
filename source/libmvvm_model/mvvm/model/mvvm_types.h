// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_MVVM_TYPES_H
#define MVVM_MODEL_MVVM_TYPES_H

#include <string>

namespace ModelView {

class SessionItem;
class SessionModel;

//! Defines constants to be used as SessionItem data role.

namespace ItemDataRole {
const int IDENTIFIER = 0; //!< unique identifier
const int DATA = 1;       //!< main data role
const int DISPLAY = 2;    //!< display name
const int APPEARANCE = 3; //!< appearance flag
const int LIMITS = 4;     //!< possibly limits on item's data
const int TOOLTIP = 5;    //!< tooltip for item's data
const int EDITORTYPE = 6; //!< type of custom editor for the data role
} // namespace ItemDataRole

enum Appearance {
    ENABLED = 1,  // enabled in Qt widgets; when disabled, will be shown in gray
    EDITABLE = 2, // editable in Qt widgets; readonly otherwise
    VISIBLE = 4   // visible in Qt widgets; doesn't appear in trees and tables otherwise
};

namespace Constants {
const std::string BaseType = "SessionItem";
const std::string ColorMapItemType = "ColorMap";
const std::string ColorMapViewportItemType = "ColorMapViewport";
const std::string CompoundItemType = "Compound";
const std::string ContainerItemType = "Container";
const std::string Data1DItemType = "Data1D";
const std::string Data2DItemType = "Data2D";
const std::string FixedBinAxisItemType = "FixedBinAxis";
const std::string GraphItemType = "Graph";
const std::string GraphViewportItemType = "GraphViewport";
const std::string GroupItemType = "Group";
const std::string LinkedItemType = "Linked";
const std::string PenItemType = "Pen";
const std::string PointwiseAxisItemType = "PointwiseAxis";
const std::string PropertyType = "Property";
const std::string TextItemType = "Text";
const std::string VectorItemType = "Vector";
const std::string ViewportAxisItemType = "ViewportAxis";
} // namespace Constants

} // namespace ModelView

#endif // MVVM_MODEL_MVVM_TYPES_H
