// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef STYLEUTILS_H
#define STYLEUTILS_H

class QSize;
class QFont;

//! Namespace for central access to all theme styling.

namespace StyleUtils
{

//! Size of tolbar icons for LayerEditor, MaterialEditor and similar.
QSize ToolBarIconSize();

//! Hint on size of docks on main reflectometry window.
QSize DockSizeHint();

//! Hint on minimum size of docks on main reflectometry window.
QSize DockMinimumSizeHint();

//! Returns font for sections (25% large than system font).
QFont sectionFont(bool bold = false);

QSize SizeOfLetterM();

int LargeButtonHeight();

}; // namespace StyleUtils

#endif // STYLEUTILS_H
